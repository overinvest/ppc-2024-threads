// Copyright 2024 Kochetov Nikolay
#include <gtest/gtest.h>

#include "core/perf/include/perf.hpp"
#include "seq/kochetov_n_gauss_filter_vertical/include/ops_seq.hpp"

TEST(kochetov_n_gauss_filter_vert_seq, test_pipeline_run) {
  // Create data
  size_t w = 1500;
  size_t h = 1500;
  float sigma = 2.0f;
  std::vector<uint32_t> img = kochetov_n_gauss::generator1(w, h);
  std::vector<float> kernel = kochetov_n_gauss::generate_kernel(sigma);
  std::vector<uint32_t> out(w * h);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(img.data()));
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(kernel.data()));
  taskDataSeq->inputs_count.emplace_back(w);
  taskDataSeq->inputs_count.emplace_back(h);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(w);
  taskDataSeq->outputs_count.emplace_back(h);

  // Create Task
  auto myTask = std::make_shared<FilterGaussVerticalTaskSequential>(taskDataSeq);

  // Create Perf attributes
  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perfAttr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  // Create and init perf results
  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  // Create Perf analyzer
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(myTask);
  perfAnalyzer->pipeline_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);
}

TEST(kochetov_n_gauss_filter_vert_seq, test_task_run) {
  // Create data
  size_t w = 1500;
  size_t h = 1500;
  float sigma = 2.0f;
  std::vector<uint32_t> img = kochetov_n_gauss::generator1(w, h);
  std::vector<float> kernel = kochetov_n_gauss::generate_kernel(sigma);
  std::vector<uint32_t> out(w * h);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(img.data()));
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(kernel.data()));
  taskDataSeq->inputs_count.emplace_back(w);
  taskDataSeq->inputs_count.emplace_back(h);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(w);
  taskDataSeq->outputs_count.emplace_back(h);

  // Create Task
  auto myTask = std::make_shared<FilterGaussVerticalTaskSequential>(taskDataSeq);

  // Create Perf attributes
  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perfAttr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  // Create and init perf results
  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  // Create Perf analyzer
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(myTask);
  perfAnalyzer->task_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);
}
