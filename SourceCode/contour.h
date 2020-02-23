#ifndef CONTOUR_H
#define CONTOUR_H
Mat cvGetContour(IplImage* src, int &contourCount)
{
    if (!src)
    {
        FILE *fp;
        fp = fopen("Error.txt", "a+");
        fprintf(fp, "\n cvGetContour Open Image Error");
        fclose(fp);
    }
    else
    {
        FILE *fp;
        fp = fopen("Error.txt", "a+");
        fprintf(fp, "\n cvGetContour Open Image Succeeded");
        fclose(fp);
    }
    IplImage* dst = cvCreateImage(cvGetSize(src), 8, 3);
    cvZero(dst);

    //Set default mem
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* contour = NULL;

    //get contours
    /*cvFindContours:
            int cvFindContours( CvArr* image, CvMemStorage* storage, CvSeq** first_contour,
                        int header_size=sizeof(CvContour), int mode=CV_RETR_LIST,
                        int method=CV_CHAIN_APPROX_SIMPLE, CvPoint offset=cvPoint(0,0) );
            image:Source
            storage:Container
            first_contour:output var, to save the first outside contour
            header_size:
                method = CV_CHAIN_CODE:	header_size >= sizeof(CvChain)
                            otherwise:	header_size >= sizeof(CvContour)
            mode:search patter
                CV_RETR_EXTERNAL: only outside contour
                CV_RETR_LIST: all contours, and put into list
                CV_RETR_CCOMP: all contours, and divide by two, first are outside, second are invalid
                CV_RETR_TREE: all contours, and restruct all levels of contours
            method: to calculate contour
                CV_CHAIN_CODE: output contours by Freeman, and multi-angle
                CV_CHAIN_APPROX_NONE: put all joint-point to point
                CV_CHAIN_APPROX_SIMPLE: only remain finals
                CV_CHAIN_APPROX_TC89_L1, CV_CHAIN_APPROX_TC89_KCOS: use the flavors of Teh-Chin
                CV_LINKS_RUNS: to link horizonal 1, only search by CV_RETR_LIST
            offset: to move all contours points
        */
    cvFindContours(src, storage, &contour, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //clean destination array

    //_contour is to save the place of first point, will be replaced by contour
    CvSeq* _contour = contour;

    //delete area whose acreage is smaller than presets
    double min_area = -1;
    double max_area = 0;
    int maxAreaIdx = -1;
    for (int iteratorIdx = 0; contour != 0; contour = contour->h_next, iteratorIdx++)
    {
        //get acreage of current contour
        double temp_area = fabs(cvContourArea(contour));

        //to get the max contour
        if (temp_area > max_area)
        {
            max_area = temp_area;
            maxAreaIdx = iteratorIdx;
        }
        //delete area whose acreage is smaller than presets
        if (temp_area < min_area)
        {
            cvSeqRemove(contour, 0);
        }

        //delete area whose acreage is not match length and width ratio
        /*
            int whRatio = 1;
            CvRect aRect = cvBoundingRect(contour, 0);
            if ((aRect.width / aRect.height) < whRatio)
            {
                cvSeqRemove(contour, 0));
            }*/
    }
    contour = _contour;

    //Count contours and save the max contour to dst
    int counter = 0;
    for (; contour !=0; contour = contour->h_next)
    {
        counter++;
        //fabs: to get area of current contours
        double temp_area = fabs(cvContourArea(contour));
        //draw the max contour
        if (temp_area == max_area)
        {
            CvScalar color = CV_RGB(8,0,8);
            cvDrawContours(dst, contour, color, color, -1, 1, 8);
        }
    }

    //test
    cvNamedWindow("Components", CV_WINDOW_NORMAL);
    cvShowImage("Components",dst);

    //deliver the number of contours to contourCount fab
    contourCount = counter;
    return cvarrToMat(dst);
}

Mat getContour(Mat src, int &contourCount, double minarea)
{
    int counter = 0;
    Mat dst, canny_output;
    if (!src.data)
    {
        FILE *fp;
        fp = fopen("Error.txt", "a+");
        fprintf(fp, "\n getContour Open Image Error");
        fclose(fp);
    }
    else
    {
        FILE *fp;
        fp = fopen("Error.txt", "a+");
        fprintf(fp, "\n getContour Open Image Succeeded");
        fclose(fp);
    }
    //pram. for findContours
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    /*
    //Reduce Noise by DILATE
    //Set Struct Element3
    Mat elementDILATE = getStructuringElement(MORPH_RECT, Size(2, 2));
    dilate(toExeCanny, toExeCanny, elementDILATE);

    //Reduce Noise by ERODE
    //Set Struct Element
    Mat elementERODE = getStructuringElement(MORPH_RECT, Size(3, 3));
    erode(toExeCanny, toExeCanny, elementERODE);
    */
    // Detect edges using canny
    Canny(src, canny_output, 100, 300);
    threshold(canny_output, canny_output, 10, 255, THRESH_BINARY);


    // Find contours
    findContours(canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE

    //mark out the max area contour
    double maxarea = 0;
    int maxAreaIdx = 0;

    for (int i = 0; i < contours.size(); i++)
    {
        double tmparea = fabs(contourArea(contours[i]));
        if (tmparea>maxarea)
        {
            maxarea = tmparea;
            maxAreaIdx = i;
        }
        //delete contours whose area is smaller than preset
        if (tmparea < minarea)
        {
            contours.erase(contours.begin() + i);
            //std::wcout << "delete a small area" << std::endl;
            continue;
        }
        else
            counter++;
        /*计算轮廓的直径宽高
        Rect aRect =boundingRect(contours[i]);
        if ((aRect.width / aRect.height)<whRatio)
        {
            //删除宽高比例小于设定值的轮廓
            contours.erase(contours.begin() + i);
            std::wcout << "delete a unnomalRatio area" << std::endl;
            continue;
            }  */
    }

    // Draw contours with different colors
    dst = Mat::zeros(canny_output.size(), CV_8UC3);

    for (int i = 0; i< contours.size(); i++)
    {
        //Random Color
        RNG rng;
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(dst, contours, i, color, 2, 8, hierarchy, 0, Point());
    }

    contourCount = counter;
    return dst;
}

#endif // CONTOUR_H
