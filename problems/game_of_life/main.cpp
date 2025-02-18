#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <utility>
#include <vector>

int aliveNeighboors(const cv::Mat1b &board, int i, int j)
{
    const uchar *row;
    int rowIdx = i - 1;
    int aliveNeighboorCounter = 0;
    if(rowIdx >= 0)
    {
        row = board.row(rowIdx).ptr<uchar>();
        if(j - 1 >= 0)
            aliveNeighboorCounter += row[j - 1];
        aliveNeighboorCounter += row[j];
        if(j + 1 < board.cols)
            aliveNeighboorCounter += row[j + 1];
    }

    row = board.row(i).ptr<uchar>();
    if(j - 1 >= 0)
        aliveNeighboorCounter += row[j - 1];
    aliveNeighboorCounter += row[j];
    if(j + 1 < board.cols)
        aliveNeighboorCounter += row[j + 1];

    rowIdx = i + 1;
    if(rowIdx < board.rows)
    {
        row = board.row(rowIdx).ptr<uchar>();
        if(j - 1 >= 0)
            aliveNeighboorCounter += row[j - 1];
        aliveNeighboorCounter += row[j];
        if(j + 1 < board.cols)
            aliveNeighboorCounter += row[j + 1];
    }

    return aliveNeighboorCounter;
}

bool checkChange(const cv::Mat1b &board, int i, int j)
{
    int aliveNeighboorCounter = aliveNeighboors(board, i, j);
    if(board.at<uchar>(i, j))
    {
        if(aliveNeighboorCounter < 2)
            return true;
        else if(aliveNeighboorCounter > 3)
            return true;
    }
    else
    {
        if(aliveNeighboorCounter == 3)
            return true;
    }
    return false;
}

void calculateNewPopulation(const cv::Mat1b &board, std::vector<std::pair<int, int>> &changes)
{
    for(int i = 0; i < board.rows; i++)
    {
        for(int j = 0; j < board.cols; j++)
        {
            if(checkChange(board, i, j))
            {
                changes.push_back(std::make_pair(i, j));
            }
        }
    }
}

int main(int argc, char **argv)
{
    cv::Mat1b board(50, 50);
    cv::randu(board, 0, 2);

    cv::namedWindow("board", cv::WINDOW_NORMAL);

    char key;
    std::vector<std::pair<int, int>> changes;
    do
    {
        calculateNewPopulation(board, changes);

        for(const std::pair<int, int> &p : changes)
        {
            board.at<uchar>(p.first, p.second) = !board.at<uchar>(p.first, p.second);
        }

        changes.clear();
        cv::imshow("board", board * 255);
        key = cv::waitKey(100);
    } while(key != 27);

    return 0;
}
