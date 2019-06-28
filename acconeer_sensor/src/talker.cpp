#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "ros/ros.h"
#include "acconeer_sensor/sensData.h"
#include "acc_driver_hal.h"
#include "acc_rss.h"
#include "acc_service.h"
#include "acc_service_envelope.h"
#include "acc_sweep_configuration.h"

#include "acc_version.h"

typedef struct
{
	uint16_t     data_length;
	uint_fast8_t sweep_count;
} envelope_callback_user_data_t;

static acc_service_status_t execute_envelope_with_blocking_calls(acc_service_configuration_t envelope_configuration, acc_sweep_configuration_t sweep_configuration);

static acc_hal_t hal;
uint16_t sensora[620];
uint16_t sensorb[620];
uint16_t sensorc[620];
uint16_t sensord[620];

int main(int argc, char **argv)
{
    	printf("Acconeer software version %s\n", ACC_VERSION);
	printf("Acconeer RSS version %s\n", acc_rss_version());

	if (!acc_driver_hal_init())
	{
		return EXIT_FAILURE;
	}

	hal = acc_driver_hal_get_implementation();

	if (!acc_rss_activate_with_hal(&hal))
	{
		return EXIT_FAILURE;
	}

	acc_service_configuration_t envelope_configuration = acc_service_envelope_configuration_create();
	

	if (envelope_configuration == NULL)
	{
		printf("acc_service_envelope_configuration_create() failed\n");
		return EXIT_FAILURE;
	}

	acc_sweep_configuration_t sweep_configuration = acc_service_get_sweep_configuration(envelope_configuration);

	if (sweep_configuration == NULL)
	{
		printf("acc_service_get_sweep_configuration() failed\n");
		return EXIT_FAILURE;
	}

	acc_service_status_t service_status;

	service_status = execute_envelope_with_blocking_calls(envelope_configuration, sweep_configuration);

	if (service_status != ACC_SERVICE_STATUS_OK)
	{
		printf("execute_envelope_with_blocking_calls() => (%u) %s\n", (unsigned int)service_status, acc_service_status_name_get(
			       service_status));
		acc_service_envelope_configuration_destroy(&envelope_configuration);
		return EXIT_FAILURE;
	}


	acc_service_envelope_configuration_destroy(&envelope_configuration);

	acc_rss_deactivate();

	ros::init(argc, argv, "arrayPublisher");

	ros::NodeHandle n;

	ros::Publisher pub = n.advertise<acconeer_sensor::sensData>("chatter", 1000);
	ros::Rate loop_rate(1);
	acconeer_sensor::sensData msg;
	while (ros::ok())
	{
		for (int i = 0; i < 620; i++)
		{
			//assign array a random number between 0 and 255.
			msg.sensor1[i]=sensora[i];
			msg.sensor2[i]=sensorb[i];
			msg.sensor3[i]=sensorc[i];
			msg.sensor4[i]=sensord[i];
		}
		//Publish array
		pub.publish(msg);
		//Let the world know
		ROS_INFO("I published something!");
		//Do this.
		ros::spinOnce();
		//Added a delay so not to spam
		loop_rate.sleep();
	}
	return 0;
}

acc_service_status_t execute_envelope_with_blocking_calls(acc_service_configuration_t envelope_configuration,acc_sweep_configuration_t sweep_configuration)
{
	acc_sweep_configuration_sensor_set(sweep_configuration, 1);
	acc_service_handle_t handle1 = acc_service_create(envelope_configuration);

	if (handle1 == NULL)
	{
		printf("sensor1 acc_service_create failed\n");
		return ACC_SERVICE_STATUS_FAILURE_UNSPECIFIED;
	}



	acc_sweep_configuration_sensor_set(sweep_configuration, 2);
	acc_service_handle_t handle2 = acc_service_create(envelope_configuration);

	if (handle2 == NULL)
	{
		printf("sensor2 acc_service_create failed\n");
		return ACC_SERVICE_STATUS_FAILURE_UNSPECIFIED;
	}


	acc_sweep_configuration_sensor_set(sweep_configuration, 3);
	acc_service_handle_t handle3 = acc_service_create(envelope_configuration);

	if (handle3 == NULL)
	{
		printf("sensor 3 acc_service_create failed\n");
		return ACC_SERVICE_STATUS_FAILURE_UNSPECIFIED;
	}

	acc_sweep_configuration_sensor_set(sweep_configuration, 4);
	acc_service_handle_t handle4 = acc_service_create(envelope_configuration);

	if (handle4 == NULL)
	{
		printf("sensor 4 acc_service_create failed\n");
		return ACC_SERVICE_STATUS_FAILURE_UNSPECIFIED;
	}

	acc_service_envelope_metadata_t envelope_metadata1;
	acc_service_envelope_get_metadata(handle1, &envelope_metadata1);

	uint16_t envelope_data1[envelope_metadata1.data_length];


	acc_service_envelope_metadata_t envelope_metadata2;
	acc_service_envelope_get_metadata(handle2, &envelope_metadata2);

	uint16_t envelope_data2[envelope_metadata2.data_length];


	acc_service_envelope_metadata_t envelope_metadata3;
	acc_service_envelope_get_metadata(handle3, &envelope_metadata3);

	uint16_t envelope_data3[envelope_metadata3.data_length];


	acc_service_envelope_metadata_t envelope_metadata4;
	acc_service_envelope_get_metadata(handle4, &envelope_metadata4);

	uint16_t envelope_data4[envelope_metadata4.data_length];



	acc_service_envelope_result_info_t result_info;


	acc_service_status_t service_status1 = acc_service_activate(handle1);
	if (service_status1 == ACC_SERVICE_STATUS_OK)
	{


		service_status1 = acc_service_envelope_get_next(handle1, envelope_data1, envelope_metadata1.data_length, &result_info);

		if (service_status1 == ACC_SERVICE_STATUS_OK)
		{
			for (uint_fast16_t index = 0; index < envelope_metadata1.data_length; index++)
			{
				

				sensora[index] = envelope_data1[index];
			}
		}
		else
		{
			printf("Envelope data not properly retrieved\n");
		}



		service_status1 = acc_service_deactivate(handle1);
	}
	else
	{
		printf("acc_service_activate() %u => %s\n", (unsigned int)service_status1, acc_service_status_name_get(service_status1));
	}


	acc_service_status_t service_status2 = acc_service_activate(handle2);

	if (service_status2 == ACC_SERVICE_STATUS_OK)
	{


		service_status2 = acc_service_envelope_get_next(handle2, envelope_data2, envelope_metadata2.data_length, &result_info);

		if (service_status2 == ACC_SERVICE_STATUS_OK)
		{
			for (uint_fast16_t index = 0; index < envelope_metadata2.data_length; index++)
			{
				

				sensorb[index] = envelope_data2[index];
			}

			printf("\n");
		}
		else
		{
			printf("Envelope data not properly retrieved\n");
		}



		service_status2 = acc_service_deactivate(handle2);
	}
	else
	{
		printf("acc_service_activate() %u => %s\n", (unsigned int)service_status2, acc_service_status_name_get(service_status2));
	}


	acc_service_status_t service_status3 = acc_service_activate(handle3);
	if (service_status3 == ACC_SERVICE_STATUS_OK)
	{

		service_status3 = acc_service_envelope_get_next(handle3, envelope_data3, envelope_metadata3.data_length, &result_info);

		if (service_status3 == ACC_SERVICE_STATUS_OK)
		{
			for (uint_fast16_t index = 0; index < envelope_metadata3.data_length; index++)
			{
				

				sensorc[index] = envelope_data3[index];
			}

			printf("\n");
		}
		else
		{
			printf("Envelope data not properly retrieved\n");
		}


		service_status3 = acc_service_deactivate(handle3);
	}
	else
	{
		printf("acc_service_activate() %u => %s\n", (unsigned int)service_status3, acc_service_status_name_get(service_status3));
	}




	acc_service_status_t service_status4 = acc_service_activate(handle4);

	if (service_status4 == ACC_SERVICE_STATUS_OK)
	{

		service_status4 = acc_service_envelope_get_next(handle4, envelope_data4, envelope_metadata4.data_length, &result_info);

		if (service_status4 == ACC_SERVICE_STATUS_OK)
		{
			for (uint_fast16_t index = 0; index < envelope_metadata4.data_length; index++)
			{
				

				sensord[index] = envelope_data4[index];
			}

			printf("\n");
		}
		else
		{
			printf("Envelope data not properly retrieved\n");
		}


		service_status4 = acc_service_deactivate(handle4);
	}
	else
	{
		printf("acc_service_activate() %u => %s\n", (unsigned int)service_status4, acc_service_status_name_get(service_status4));
	}

	acc_service_destroy(&handle1);
	acc_service_destroy(&handle2);
	acc_service_destroy(&handle3);
	acc_service_destroy(&handle4);

	return service_status4;
}

