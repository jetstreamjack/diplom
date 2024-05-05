#include <stdlib.h>
#include <stdio.h>

#include <QCoreApplication>

#include <vector>
#include <memory>
#include "balancer.h"
#include "gpu_controller.h"
#include "connection_observer.h"
#include "connection_controller.h"
#include "server.h"

int main(int argc, char ** argv)
{
	QCoreApplication a(argc, argv);

	cudaError_t error;
	error = cudaGetLastError();
	if (error != cudaSuccess)
  	{
  		qDebug() << cudaGetErrorString(error) << '\n';
  		exit(1);
  	}

	auto gpuController = std::make_unique<controller::GpuController>(); 
	auto balancer = std::make_unique<balancer::Balancer>(std::move(gpuController));
	
	auto connectionController = std::make_shared<connection_controller::ConnectionController>(std::move(balancer));
	auto connectionObserver = std::make_shared<connection::ConnectionObserver>();

	auto server = std::make_unique<server::Server>(connectionController, connectionObserver);

	server->Run(std::string{""});

	return a.exec();
}
