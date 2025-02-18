#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
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

cv::Mat1b board(120, 160);
bool dragging = false;

void showBoard()
{
    cv::Mat1b resized;
    cv::resize(board, resized, cv::Size(1920, 1080));
    cv::imshow("board", resized * 255);
}

void changeBoardAtPosition(int x, int y)
{
    std::cout << x << ", " << y;
    x = int(x * (board.cols / 1920.));
    y = int(y * (board.rows / 1080.));
    std::cout << " - " << x << ", " << y << std::endl;
    board.at<uchar>(y, x) = !board.at<uchar>(y, x);
}

void mouseCallback(int event, int x, int y, int flags, void *userdata)
{
    if(event == cv::EVENT_LBUTTONDOWN)
    {
        changeBoardAtPosition(x, y);
        dragging = true;
    }
    else if(event == cv::EVENT_LBUTTONUP)
    {
        dragging = false;
    }
    else if(event == cv::EVENT_MOUSEMOVE && dragging)
    {
        changeBoardAtPosition(x, y);
    }
    showBoard();
}

int main(int argc, char **argv)
{
    cv::randu(board, 0, 2);

    cv::namedWindow("board", cv::WINDOW_KEEPRATIO);
    cv::setMouseCallback("board", mouseCallback);

    showBoard();
    char key = cv::waitKey();
    std::vector<std::pair<int, int>> changes;

    while(key != 27)
    {
        calculateNewPopulation(board, changes);

        for(const std::pair<int, int> &p : changes)
        {
            board.at<uchar>(p.first, p.second) = !board.at<uchar>(p.first, p.second);
        }

        changes.clear();
        cv::Mat1b resized;
        cv::resize(board, resized, cv::Size(1920, 1080));

        cv::imshow("board", resized * 255);
        key = cv::waitKey(100);
        if(key == 32)
            key = cv::waitKey();
    }

    return 0;
}
