/*
 * This software is distributed under BSD 3-clause license (see LICENSE file).
 *
 * Authors: Evangelos Anagnostopoulos, Heiko Strathmann
 */
#include <gtest/gtest.h>
#include <shogun/features/RandomFourierDotFeatures.h>


using namespace shogun;

TEST(RandomFourierDotFeatures, dot_test)
{
	int32_t num_dims = 50;
	int32_t num_vecs = 5;
	int32_t num_dims_rff = 100;

	SGMatrix<float64_t> w(num_dims+1,num_dims_rff);

	for (index_t i=0; i<num_dims_rff; i++)
	{
		for (index_t j=0; j<num_dims; j++)
			w(j,i) = i+j;
		w(num_dims,i) = 1;
	}

	SGMatrix<int32_t> data(num_dims, num_vecs);
	for (index_t i=0; i<num_vecs; i++)
	{
		for (index_t j=0; j<num_dims; j++)
			data(j,i) = i+j;
	}

	auto d_feats = std::make_shared<DenseFeatures<int32_t>>(data);
	SGVector<float64_t> params(1);
	params[0] = 8;
	auto r_feats = std::make_shared<RandomFourierDotFeatures>(
			d_feats, num_dims_rff, GAUSSIAN, params, w);

	SGMatrix<float64_t> cross_dot_matrix(num_vecs, num_vecs);
	for (index_t i=0; i<num_vecs; i++)
	{
		for (index_t j=0; j<num_vecs; j++)
		{
			cross_dot_matrix(i,j) = r_feats->dot(i,r_feats,j);
		}
	}

	float64_t e = 1e-13;
	float64_t mat []= {
		1.00555015129804581, 0.0502863828725347,
		0.00023246982925897, -0.02515703711183189,
		-0.00876801723029572, 0.05028638287253472,
		1.00104181673378067, 0.02521590366359591,
		-0.00354749195264035, -0.01140342190110809,
		0.00023246982925894, 0.02521590366359589,
		0.99726185495188157, 0.03896951887431968,
		-0.00074544906564935, -0.02515703711183188,
		-0.00354749195264038, 0.03896951887431966,
		1.00006389783887250, 0.02708505456315889,
		-0.00876801723029571, -0.01140342190110809,
		-0.00074544906564934, 0.02708505456315890,
		0.99501156944854796};

	SGMatrix<float64_t> precomputed_mat(mat, 5, 5, false);
	for (index_t i=0; i<5; i++)
	{
		for (index_t j=0; j<5; j++)
			EXPECT_NEAR(precomputed_mat(i,j), cross_dot_matrix(i,j), e);
	}

}

TEST(RandomFourierDotFeatures, dense_dot_test)
{
	int32_t num_dims = 50;
	int32_t num_vecs = 5;
	int32_t num_dims_rff = 100;

	SGMatrix<float64_t> w(num_dims+1,num_dims_rff);

	for (index_t i=0; i<num_dims_rff; i++)
	{
		for (index_t j=0; j<num_dims; j++)
			w(j,i) = i+j;
		w(num_dims,i) = 1;
	}

	SGMatrix<int32_t> data(num_dims, num_vecs);
	for (index_t i=0; i<num_vecs; i++)
	{
		for (index_t j=0; j<num_dims; j++)
			data(j,i) = i+j;
	}

	auto d_feats = std::make_shared<DenseFeatures<int32_t>>(data);
	SGVector<float64_t> params(1);
	params[0] = 8;
	auto r_feats = std::make_shared<RandomFourierDotFeatures>(
			d_feats, num_dims_rff, GAUSSIAN, params, w);

	SGMatrix<float64_t> cross_dot_matrix(num_vecs, num_vecs);
	for (index_t i=0; i<num_vecs; i++)
	{
		for (index_t j=0; j<num_vecs; j++)
		{
			cross_dot_matrix(i,j) = r_feats->dot(i,r_feats,j);
		}
	}

	float64_t e = 1e-13;
	float64_t vec[] = {0.0449317122413237, -0.2909428095069972, -0.0361875564777414, 0.1185535017124422,
					-0.0018001695930624};
	SGVector<float64_t> precomputed_vec(vec, 5, false);
	for (index_t i=0; i<5; i++)
	{
		SGVector<float64_t> ones(num_dims_rff);
		SGVector<float64_t>::fill_vector(ones.vector, ones.vlen, 1);
		float64_t dot = r_feats->dot(i, ones);
		EXPECT_NEAR(dot, vec[i], e);
	}

}

TEST(RandomFourierDotFeatures, add_to_dense_test)
{
	int32_t num_dims = 50;
	int32_t num_vecs = 5;
	int32_t num_dims_rff = 100;

	SGMatrix<float64_t> w(num_dims+1,num_dims_rff);

	for (index_t i=0; i<num_dims_rff; i++)
	{
		for (index_t j=0; j<num_dims; j++)
			w(j,i) = i+j;
		w(num_dims,i) = 1;
	}

	SGMatrix<int32_t> data(num_dims, num_vecs);
	for (index_t i=0; i<num_vecs; i++)
	{
		for (index_t j=0; j<num_dims; j++)
			data(j,i) = i+j;
	}

	auto d_feats = std::make_shared<DenseFeatures<int32_t>>(data);
	SGVector<float64_t> params(1);
	params[0] = 8;
	auto r_feats = std::make_shared<RandomFourierDotFeatures>(
			d_feats, num_dims_rff, GAUSSIAN, params, w);

	SGMatrix<float64_t> cross_dot_matrix(num_vecs, num_vecs);
	for (index_t i=0; i<num_vecs; i++)
	{
		for (index_t j=0; j<num_vecs; j++)
		{
			cross_dot_matrix(i,j) = r_feats->dot(i,r_feats,j);
		}
	}

	float64_t e = 1e-13;
	float64_t vec[] = {0.0449317122413237, -0.2909428095069972, -0.0361875564777414, 0.1185535017124422,
					-0.0018001695930624};
	SGVector<float64_t> precomputed_vec(vec, 5, false);
	for (index_t i=0; i<5; i++)
	{
		SGVector<float64_t> zeros(num_dims_rff);
		SGVector<float64_t>::fill_vector(zeros.vector, zeros.vlen, 0);
		r_feats->add_to_dense_vec(1, i, zeros.vector, zeros.vlen, false);
		float64_t sum = 0;
		for (index_t j=0; j<num_dims_rff; j++)
			sum += zeros[j];
		EXPECT_NEAR(sum, vec[i], e);
	}

}

TEST(RandomFourierDotFeatures, dim_output)
{
	int32_t num_dims = 50;
	int32_t num_vecs = 5;
	int32_t num_dims_rff = 100;

	SGMatrix<float64_t> data(num_dims, num_vecs, false);
	auto d_feats = std::make_shared<DenseFeatures<float64_t>>(data);
	SGVector<float64_t> params(1);
	params[0] = 8;
	auto r_feats = std::make_shared<RandomFourierDotFeatures>(
	    d_feats, num_dims_rff, GAUSSIAN, params);

	auto rows = r_feats->get_dim_feature_space();
	auto cols = r_feats->get_num_vectors();

	EXPECT_EQ(rows, num_dims_rff);
	EXPECT_EQ(cols, num_vecs);
}


