#ifndef CANNY_H
#define CANNY_H
Mat getCanny(Mat toExeCanny)
{   //using Canny to get the edge of object by Lwz 2017.05.01
    Mat CannyExecute;

    //Reduce Noise by DILATE
    //Set Struct Element
    Mat elementDILATE = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(toExeCanny, toExeCanny, elementDILATE);

    //Reduce Noise by ERODE
    //Set Struct Element
    Mat elementERODE = getStructuringElement(MORPH_RECT, Size(3, 3));
    erode(toExeCanny, toExeCanny, elementERODE);

    Canny(toExeCanny, CannyExecute, 190, 300);
    threshold(CannyExecute, CannyExecute, 250, 255, THRESH_BINARY);
    return CannyExecute;
}
#endif // CANNY_H
