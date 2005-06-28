cache_size=50;
C=10;
numtrain=1000;
svm_eps=1e-2;
svm_tube=0.01;
W1=0.5;
W2=2;
W3=1;

rand('state',0);
%rand('state',sum(100*clock));
traindat=[sort(100*rand(1,numtrain))];
traindat=[traindat(2:490) traindat(512:1000)];
trainlab=[sin(2*traindat)];
testdat=[linspace(-10,traindat(1),30) traindat linspace(traindat(end),traindat(end)+traindat(1)+10,30)];
testlab=[sin(testdat)];

%gf('send_command', 'loglevel ALL');
%gf('send_command', 'new_svm LIBSVR');
%gf('set_features', 'TRAIN', traindat);
%gf('set_labels', 'TRAIN', trainlab);
%gf('send_command', 'set_kernel GAUSSIAN REAL 50 10');
%gf('send_command', 'init_kernel TRAIN');
%gf('send_command', sprintf('c %f',C));
%gf('send_command', sprintf('svm_epsilon %f',svm_eps));
%gf('send_command', sprintf('svr_tube_epsilon %f',svm_tube));
%tic; gf('send_command', 'svm_train'); toc;
%[b, alphas]=gf('get_svm');
%gf('set_features', 'TEST', testdat);
%gf('set_labels', 'TEST', testlab);
%gf('send_command', 'init_kernel TEST');
%out=gf('svm_classify');

gf('send_command', 'new_svm SVRLIGHT');
gf('clean_features', 'TRAIN' );
gf('add_features','TRAIN', traindat);
gf('add_features','TRAIN', traindat);
gf('add_features','TRAIN', traindat);
gf('set_labels', 'TRAIN', trainlab);
gf('send_command', sprintf('set_kernel COMBINED %d', cache_size));
gf('send_command', sprintf('add_kernel 1 GAUSSIAN REAL %d %f', cache_size, W1));
gf('send_command', sprintf('add_kernel 1 GAUSSIAN REAL %d %f', cache_size, W2));
gf('send_command', sprintf('add_kernel 1 GAUSSIAN REAL %d %f', cache_size, W3));
gf('send_command', 'init_kernel TRAIN');
gf('send_command', 'use_mkl 1');
gf('send_command', 'use_precompute 1');
gf('send_command', 'mkl_parameters 1e-3 0');
gf('send_command', sprintf('c %f',C));
gf('send_command', sprintf('svm_epsilon %f',svm_eps));
gf('send_command', sprintf('svr_tube_epsilon %f',svm_tube));
tic; gf('send_command', 'svm_train'); toc;
[b2, alphas2]=gf('get_svm');
gf( 'clean_features', 'TEST' );
gf('add_features','TEST', testdat);
gf('add_features','TEST', testdat);
gf('add_features','TEST', testdat);
gf('set_labels', 'TEST', testlab);
gf('send_command', 'init_kernel TEST');
out2=gf('svm_classify');

clf
plot(traindat,trainlab,'b-')
hold on
plot(traindat,trainlab,'bx')

%plot(testdat,out,'r-')
%plot(testdat,out,'ro')

plot(testdat,out2,'g-')
plot(testdat,out2,'go')
ws=gf('get_subkernel_weights');
