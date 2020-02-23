#ifndef CONTOURMATCH_H
#define CONTOURMATCH_H
Mat contourMatch(Mat ExeCanny, bool &MatchFlag)
{   //mark out contour if match source video by Lwz 2017.05.01
    //in:Canny-Executed Mat, Match flag
    //out:the match canny(preset)
    //size of video
    int const m = 320;
    int const n = 240;
    Mat FoundMatch;
    //Save ExeCanny To "temp.out"
    SaveMats(ExeCanny, 0, 1, 5, 0);

    //define tempo input name
    char *SampleName = new char[100];
    char *TempName = new char[100];
    char *MatchName = new char[100];
    for (int count = 0; count < 3; count++)
    {
        MatchFlag = 1;
        char SampleArray[m][n];
        char TempArray[m][n];

        //string IndexSampleNameString = std::to_string(imgIndex);
        //string FileName = FileSource + IndexSampleNameString;
        sprintf(SampleName, "lib%d.out", count);
        sprintf(TempName, "temp.out");
        FILE *fp_s;
        FILE *fp_t;
        //input .out to compare
        fp_s = fopen(SampleName, "a+");
        fp_t = fopen(TempName, "a+");
        if (fp_s == NULL || fp_t == NULL)
        {
            continue;
        }
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                //input .out
                fscanf (fp_s, "%c", &SampleArray[i][j]);
                fscanf (fp_t, "%c", &TempArray[i][j]);
                //compare
                if (SampleArray[i][j] != TempArray[i][j])
                {
                    MatchFlag = 0;
                    break;
                }
            }
            fscanf(fp_s, "\n");
            fscanf(fp_t, "\n");
        }
        fclose(fp_s);
        fclose(fp_t);

        //if match mat found, trans the mat to FoundMatch and return to caller
        if (MatchFlag == 1)
        {
            sprintf(MatchName, "lib%d.jpg", count);
            FoundMatch = imread(MatchName);
            break;
        }
    }
    return FoundMatch;
}


#endif // CONTOURMATCH_H
