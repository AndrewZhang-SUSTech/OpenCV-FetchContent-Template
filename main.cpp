#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**){
    std::cout << "Hello, from Experiment!\n";
    cv::Mat image = cv::imread("path/to/image.jpg");
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!\n";
        return -1;
    }
    cv::imshow("Display Image", image);
    cv::waitKey(0); // Wait for a keystroke in the window
    return 0;
}
