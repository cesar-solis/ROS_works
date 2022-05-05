#include "ros/ros.h"         //libreria de ros
#include "std_msgs/String.h"// libreria de estructura


void chatterCallback(const std_msgs::String::ConstPtr& exch) //Funcion chatterCallback el cual va a tomar a la variable exch de tipo string del paquete std_msgs usando un puntero
{
  ROS_INFO("Recibiendo: (%s) del nodo Sub_Pub ", exch->data.c_str()); //Imprime en el shell el texto y extrae el valor data de la variable msg,la cual esta siendo enviada por el publisher, en este 
}									//caso del nodo_sub_pub en modo publisher y la convierte en un tipo string para ser impresa

int main(int argc, char **argv)           //Funcion Main
{
  
  ros::init(argc, argv, "Nodo_Sub");      //Inicializa el nodo de nombre Nodo_Sub

  ros::NodeHandle n; 			   // Punto de acceso principal para comunicarse con el sistema ROS y tambien va a inicializar el nodo, se crea un objeto n de la clase NodeHandle

  ros::Subscriber sub = n.subscribe("T_Sub_Pub_to_Sub", 1000, chatterCallback); /* Le avisa al nodo maestro de ROS que se va a suscribir al topic "T_Sub_Pub_to_Sub" a traves de la 
  	funcion subscribe() de tipo NodeHandle. ROS llamara a la funcion chatterCallback cada vez que se recibe un mensaje 
  	* 1000 es el tamaño del buffer por si se pierde informacion  */
  ros::spin(); //Realiza el bucle

  return 0;
}
