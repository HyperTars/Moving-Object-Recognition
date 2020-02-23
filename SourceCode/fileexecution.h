#ifndef FILEEXECUTION_H
#define FILEEXECUTION_H
/***************************************************************
 * File & VideoInput Execution by Lwz 2017.02.22
 * Save Source Video Frames to a MatArray or a Mat
 ****************************************************************/
//Open Video Source and Save Frames to an MatArray
MatArray FileExecute(string FileAddress)
{
    //Save VideoFrame
    MatArray VideoFrame;
    //Set FrameCounter
    VideoFrame.counter = 0;
    //open source video file
    VideoCapture sourceVideo(FileAddress);
    if (!sourceVideo.isOpened())
    {
        FILE *fp;
        fp = fopen("Error.txt", "a+");
        fprintf(fp, "\nVideo Open Error");
        fclose(fp);
        exit(1);
    }
    else
    {
        FILE *fp;
        fp = fopen("Error.txt", "a+");
        fprintf(fp, "\nVideo Open Succeed");
        fclose(fp);
    }
    //create frame false flag
    bool stop(false);
    while (!stop)
    {
        //execute only if frame exist
        if (!sourceVideo.read(VideoFrame.Frame[VideoFrame.counter]))
        {
            break;
        }
        VideoFrame.counter++;
    }
    VideoFrame.counter--;
    return VideoFrame;
}

//Save Mats to disk file
bool SaveMatArray(MatArray ToSave, bool isSaveImg, bool isSaveOut, int SaveType)
{
    string MatType;
    switch (SaveType) {
    case 1:
    {
        MatType = "Source";
        break;
    }
    case 2:
    {
        MatType = "Gauss";
        break;
    }
    case 3:
    {
        MatType = "Contour";
        break;
    }
    case 4:
    {
        MatType = "Canny";
        break;
    }
    default:
        break;
    }

    char *imageSaveName = new char[100];
    char *matrixSaveName = new char[100];
    int imgIndex(0);

    for (int count = 0; count <= ToSave.counter; count++)
    {
        string imgIndexString = std::to_string(imgIndex);
        string FileName = MatType + imgIndexString;
        if (isSaveImg)
        {//Save mat as .jpg     
            sprintf(imageSaveName, "image_%s.jpg", FileName.c_str());
            imwrite(imageSaveName, ToSave.Frame[imgIndex]);
        }

        if (isSaveOut)
        {//Save mat as .out
            sprintf(matrixSaveName, "mat_%s.out", FileName.c_str());
            IplImage temp = ToSave.Frame[imgIndex];

            int m = temp.height;
            int n = temp.width;

            //distribute Mem
            int **p;
            p = new int *[m];
            for (int i = 0; i < m; i++)
            {
                p[i] = new int[n];
            }

            FILE *fp;
            fp = fopen(matrixSaveName, "w");

            uchar *ptr;
            for (int i = 0; i < m; i++)
            {
                ptr = (uchar*)temp.imageData + i*temp.widthStep;
                for (int j = 0; j < n; j++)
                {
                    p[i][j] = (int) *(ptr + j);
                    //if Grey pixel vary from 100 to 255, shows 0
                    if (p[i][j] > 100)
                        fprintf(fp, "0");
                    //else pixel vary from 0 to 100, shows 1
                    else
                        fprintf(fp, "1");
                }
                fprintf(fp, "\n");
            }
            fclose(fp);
        }
        imgIndex++;
    }
    return 1;
}

bool SaveMats(Mat ToSave, bool isSaveImg, bool isSaveOut, int SaveType, int imgIndex)
{
    string MatType;
    switch (SaveType) {
    case 1:
    {
        MatType = "Source";
        break;
    }
    case 2:
    {
        MatType = "Gauss";
        break;
    }
    case 3:
    {
        MatType = "Contour";
        break;
    }
    case 4:
    {
        MatType = "Canny";
        break;
    }

    case 5:
    {
        MatType = "temp";
    }
    default:
        break;
    }

    char *imageSaveName = new char[100];
    char *matrixSaveName = new char[100];

    //for (int count = 0; count <= ToSave.counter; count++)
    //{
        string imgIndexString = std::to_string(imgIndex);
        string FileName = MatType + imgIndexString;
        if (isSaveImg)
        {//Save mat as .jpg
            sprintf(imageSaveName, "image_%s.jpg", FileName.c_str());
            imwrite(imageSaveName, ToSave);
        }

        if (isSaveOut)
        {//Save mat as .out
            sprintf(matrixSaveName, "mat_%s.out", FileName.c_str());
            if (MatType == "temp")
                sprintf(matrixSaveName, "temp.out");
            IplImage temp = ToSave;

            int m = temp.height;
            int n = temp.width;

            //distribute Mem
            int **p;
            p = new int *[m];
            for (int i = 0; i < m; i++)
            {
                p[i] = new int[n];
            }

            FILE *fp;
            fp = fopen(matrixSaveName, "w");

            uchar *ptr;
            for (int i = 0; i < m; i++)
            {
                ptr = (uchar*)temp.imageData + i*temp.widthStep;
                for (int j = 0; j < n; j++)
                {
                    p[i][j] = (int) *(ptr + j);
                    //if Grey pixel vary from 100 to 255, shows 0
                    if (p[i][j] > 100)
                        fprintf(fp, "0");
                    //else pixel vary from 0 to 100, shows 1
                    else
                        fprintf(fp, "1");
                }
                fprintf(fp, "\n");
            }
            fclose(fp);
        }
    //}
    return 1;
}
//Qt Open File And Return File Address
QImage Mat2QImage(Mat Source)
{
    //Trans Mat To QImage
    if (Source.data)
    {
        //Mat TO QImage
        cv::cvtColor(Source, Source, CV_BGR2RGB);
        QImage tempQimg = QImage((const unsigned char *)(Source.data), Source.cols, Source.rows, QImage::Format_RGB888);
        return tempQimg;
    }
}

#endif // FILEEXECUTION_H
