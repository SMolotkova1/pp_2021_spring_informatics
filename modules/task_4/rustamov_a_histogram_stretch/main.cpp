// Copyright 2021 Rustamov Azer

#include <gtest/gtest.h>

#include <random>
#include <iostream>
#include "../../../modules/task_4/rustamov_a_histogram_stretch/histogram_stretch.h"

TEST(Histogram_Stretch, Incorrect_Image) {
    int w = 0, h = 10;
    ASSERT_ANY_THROW(generate_random_image(w, h));
}

TEST(Histogram_Stretch, Correct_Stretch_Histogram_Parallel) {
    int min_y, max_y;
    int w = 500, h = 500;
    Matrix str_hist_seq(256), str_hist_std(256);
    Matrix image = generate_random_image(w, h);
    Matrix hist = make_histogram(image, w, h);
    min_y = get_min_y(hist);
    max_y = get_max_y(hist);

    Matrix res_seq = increase_contrast(image, w, h, min_y, max_y);
    Matrix res_std = increase_contrast_std(image, w, h, min_y, max_y);
    for (int i = 0; i < h * w; i++) {
        ASSERT_EQ(res_seq[i], res_std[i]);
    }
}

TEST(Histogram_Stretch, Histogram_Of_Result_Equal_To_Stretched_Histogram) {
    int w = 100, h = 100;
    Matrix image = generate_random_image(w, h);
    Matrix histogram = make_histogram(image, w, h);
    int min_y, max_y;
    min_y = get_min_y(histogram);
    max_y = get_max_y(histogram);
    Matrix str_histogram = stretch_histogram(histogram, min_y, max_y);
    Matrix result = histogram_sretch_algorithm(image, w, h);
    Matrix res_histogram = make_histogram(result, w, h);
    for (int i = 0; i < 256; i++) {
        ASSERT_EQ(str_histogram[i], res_histogram[i]);
    }
}

TEST(Histogram_Stretch, Correct_Stretching_2x2) {
    int w = 2, h = 2;
    Matrix image = { 0, 1,
                     1, 0 };
    Matrix exp_result = { 0, 255,
                         255, 0 };
    Matrix histogram = make_histogram(image, w, h);
    Matrix result = histogram_sretch_algorithm_std(image, w, h);
    for (int i = 0; i < h * w; i++) {
        ASSERT_EQ(result[i], exp_result[i]);
    }
}

TEST(Histogram_Stretch, Correct_Stretching_10x10) {
    int w = 10, h = 10;
    Matrix image = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    Matrix exp_result = { 0, 28, 57, 85, 113, 142, 170, 198, 227, 255,
                          0, 28, 57, 85, 113, 142, 170, 198, 227, 255,
                          0, 28, 57, 85, 113, 142, 170, 198, 227, 255,
                          0, 28, 57, 85, 113, 142, 170, 198, 227, 255,
                          0, 28, 57, 85, 113, 142, 170, 198, 227, 255,
                          0, 28, 57, 85, 113, 142, 170, 198, 227, 255,
                          0, 28, 57, 85, 113, 142, 170, 198, 227, 255,
                          0, 28, 57, 85, 113, 142, 170, 198, 227, 255,
                          0, 28, 57, 85, 113, 142, 170, 198, 227, 255,
                          0, 28, 57, 85, 113, 142, 170, 198, 227, 255, };
    Matrix histogram = make_histogram(image, w, h);
    Matrix result = histogram_sretch_algorithm_std(image, w, h);
    for (int i = 0; i < h * w; i++) {
        ASSERT_EQ(result[i], exp_result[i]);
    }
}

TEST(Histogram_Stretch, Cannot_Stretch_Twice) {
    int w = 100, h = 100;
    Matrix image = generate_random_image(w, h);
    Matrix result = histogram_sretch_algorithm_std(image, w, h);
    Matrix second_result = histogram_sretch_algorithm_std(result, w, h);
    for (int i = 0; i < h * w; i++) {
        ASSERT_EQ(result[i], second_result[i]);
    }
}

TEST(Histogram_Stretch, Correct_Stretching_500x500) {
    int w = 500, h = 500;
    Matrix image = generate_random_image(w, h);
    Matrix result_seq = histogram_sretch_algorithm(image, w, h);
    Matrix result_std = histogram_sretch_algorithm_std(image, w, h);
    for (int i = 0; i < h * w; i++) {
        ASSERT_EQ(result_seq[i], result_std[i]);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
