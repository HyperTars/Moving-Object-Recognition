#ifndef MIXTUREOFGAUSS_H
#define MIXTUREOFGAUSS_H
MatArray MOGGuass(MatArray SourceVideoMat)
{	//Execute Mixture of Guass by Lwz 2016.03.22
    int counter = 0;
    //Define Foreground MatArray
    MatArray Foreground;
    Foreground.counter = SourceVideoMat.counter;
    //create Background Sub Tractor Mixture of Guass
    Ptr<BackgroundSubtractorMOG2> mog = createBackgroundSubtractorMOG2();
    //execute MOG
    while (counter <= SourceVideoMat.counter)
    {
        /*set mog var*/
        //越大轮廓越大
        mog->setNMixtures(25);
        //越大噪点越少，但是会导致人物割裂
        mog->setVarInit(15);
        //设置背景比例，会导致人物内部掏空
        mog->setBackgroundRatio(1);
        mog->setComplexityReductionThreshold(1000);
        //开启阴影检测
        mog->setDetectShadows(1);
        //设置阴影值
        mog->setShadowValue(10);
        //设置阴影阈值
        mog->setShadowThreshold(5);
        //设置变量阈值，越大表示提取的前景越少，可能导致人物内部掏空
        mog->setVarThreshold(90);
        //抑制远景噪声
        mog->setVarThresholdGen(800);
        //Apply All VAR
        mog->apply(SourceVideoMat.Frame[counter], Foreground.Frame[counter], 0.00000000000000001);

        //cover RGB to Grey
        normalize(Foreground.Frame[counter], Foreground.Frame[counter], 0, 255, NORM_MINMAX);
        threshold(Foreground.Frame[counter], Foreground.Frame[counter], 220, 255, THRESH_BINARY_INV);

        counter++;
    }
    return Foreground;
}

#endif // MIXTUREOFGAUSS_H
