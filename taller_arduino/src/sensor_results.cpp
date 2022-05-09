#include "ros/ros.h"         //libreria de ros
#include "std_msgs/String.h"// libreria de estructura

void chatterCallback_temp(const std_msgs::String::ConstPtr& valor_int_eng) //Funcion chatterCallback el cual va a tomar a la variable valor_int_eng de tipo string del paquete std_msgs usando un puntero
{
  
    ROS_INFO("Temperature Sensor: %s ", valor_int_eng->data.c_str()); //Imprime en el shell el texto y extrae el valor data de la variable msg,la cual esta siendo enviada por el publisher, en este 
}									//caso del nodo sensor_int_string en modo publisher y la convierte en un tipo string para ser impresa

void chatterCallback_rpm(const std_msgs::String::ConstPtr& valor_float_eng) //Funcion chatterCallback el cual va a tomar a la variable valor_float_eng de tipo string del paquete std_msgs usando un puntero
{
  
    ROS_INFO("Speed Sensor: %s ", valor_float_eng->data.c_str()); //Imprime en el shell el texto y extrae el valor data de la variable msg,la cual esta siendo enviada por el publisher, en este 
}		                                                        //caso del nodo sensor_float_string en modo publisher y la convierte en un tipo string para ser impresa

void chatterCallback_on_off(const std_msgs::String::ConstPtr& valor_bool_eng) //Funcion chatterCallback el cual va a tomar a la variable valor_bool_eng de tipo string del paquete std_msgs usando un puntero
{
  
    ROS_INFO("State: %s ", valor_bool_eng->data.c_str()); //Imprime en el shell el texto y extrae el valor data de la variable msg,la cual esta siendo enviada por el publisher, en este 
    ROS_INFO("==========================="); //caso del nodo sensor_bool_string en modo publisher y la convierte en un tipo string para ser impresa
}	

	                                                
int main(int argc, char **argv)           //Funcion Main
{
  
  ros::init(argc, argv, "sensor_results");      //Inicializa el nodo de nombre Nodo_Sub

  ros::NodeHandle n; 			   // Punto de acceso principal para comunicarse con el sistema ROS y tambien va a inicializar el nodo, se crea un objeto n de la clase NodeHandle

  ros::Subscriber sub_temp = n.subscribe("topic_int_to_string_translate", 1000, chatterCallback_temp); /* Le avisa al nodo maestro de ROS que se va a suscribir al topic       		"topic_int_to_string_translate" a traves de la funcion subscribe() de tipo NodeHandle. ROS llamara a la funcion chatterCallback_temp cada vez que se recibe un mensaje 
  	* 1000 es el tamaño del buffer por si se pierde informacion  */
  ros::Subscriber sub_rpm = n.subscribe("topic_float_to_string_translate", 1000, chatterCallback_rpm); /* Le avisa al nodo maestro de ROS que se va a suscribir al topic 	"topic_float_to_string_translate" a traves de la funcion subscribe() de tipo NodeHandle. ROS llamara a la funcion chatterCallback_rpm cada vez que se recibe un mensaje 
  	* 1000 es el tamaño del buffer por si se pierde informacion  */
  ros::Subscriber sub_on_off = n.subscribe("topic_bool_to_string_translate", 1000, chatterCallback_on_off); /* Le avisa al nodo maestro de ROS que se va a suscribir al topic 		"topic_bool_to_string_translate" a traves de la funcion subscribe() de tipo NodeHandle. ROS llamara a la funcion chatterCallback_on_off cada vez que se recibe un mensaje 
  	* 1000 es el tamaño del buffer por si se pierde informacion  */

  ros::Rate loop_rate(0.5); // Frecuencia de actualizacion de mensajes recibidos de 0.5 Hz o 2 segundos.
  
  while (ros::ok())   // Se usa un while con el condicional de que si ros esta operando se ejecuta el bucle, esto nos servira al querer matar la operacion con ctrl c 
  {                   // el cual hara que ros::ok() retorne un false y salga del bucle parando la publicacion. 
    ros::spinOnce();  //spinOnce va a llamar a todos los callback que estan esperando ser llamados en ese punto en el tiempo
    loop_rate.sleep(); // El programa duerme hasta cumplir 2 segundos y permitira llamar a los callback de manera periodica
  }

  return 0;
}
