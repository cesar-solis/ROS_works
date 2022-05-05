#include "ros/ros.h"          //Libreria de ROS
#include "std_msgs/String.h"  //Libreria de datos tipo string

#include <sstream>             //Libreria String de C++

std_msgs::String exch; // Variable global

void chatterCallback(const std_msgs::String::ConstPtr& msg1) //Sub: Funcion chatterCallback el cual va a tomar a la variable msg1 de tipo string del paquete std_msgs usando un puntero
{
  exch.data = msg1->data; // Se le asigna el valor recibido de msg1 a la variable tipo string exch el cual seria enviada a modo de intercambio entre el primer nodo hacia el ultimo nodo
  ROS_INFO("Recibi el dato: (%s) del nodo Pub ", msg1->data.c_str()); //Sub: Imprime en el shell el texto y extrae el valor data de la variable msg1,la cual esta siendo enviada por el publisher, en  
}									//este caso del nodo_pub y la convierte en un tipo string para ser impresa

int main(int argc, char **argv)  //Funcion Principal
{

  ros::init(argc, argv, "Nodo_Sub_Pub"); //Inicializa el nodo de nombre Nodo_Sub_Pub
  ros::NodeHandle n; // Punto de acceso principal para comunicarse con el sistema ROS y tambien va a inicializar el nodo, se crea un objeto n de la clase NodeHandle

  ros::Subscriber sub = n.subscribe("T_Pub_to_Sub_Pub", 1000, chatterCallback); /* Sub: Le avisa al nodo maestro de ROS que se va a suscribir al topic "T_Sub_Pub_to_Sub" a traves de la 
  	funcion subscribe() de tipo NodeHandle. ROS llamara a la funcion chatterCallback cada vez que se recibe un mensaje 
  	* 1000 es el tamaño del buffer por si se pierde informacion  */

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("T_Sub_Pub_to_Sub", 1000); /* Pub: Le avisa al nodo maestro de ROS que se va a publicar y còmo se va a 
  	publicar un mensaje de tipo string del paquete std_msgs a cualquier nodo suscrito al topic "T_Sub_Pub_to_Sub" a traves del publisher chatter_pub 
  	* 1000 es el tamaño del buffer por si se pierde informacion  */

  ros::Rate loop_rate(10); //Pub: Le da una frecuencia de muestreo de 10 mensajes por segundo o 100ms de actualizacion hasta que entre en sleep
  int count = 0; //Pub: Se le agrega un contador que llevara la cuenta de mensajes enviados
  
  // -------------------------------------------- Modo Publisher ---------------------------------------------------------------------------------------
  while (ros::ok())   // Se usa un while con el condicional de que si ros esta operando se ejecuta el bucle, esto nos servira al querer matar la operacion con ctrl c 
  {                   // el cual hara que ros::ok() retorne un false y salga del bucle parando la publicacion. 

    std::stringstream ss; // se crea un objeto ss de tipo stringstream del paquete standard de c++
    ss << exch <<" "<< count; // se le rellena el objeto ss con el dato deseado
    exch.data = ss.str(); // Se le asigna el stringstream creado a la variable exch el cual tiene estructura data ya que es un string
    
    ROS_INFO("Enviando al nodo Sub: (%s) ", exch.data.c_str()); // Visualiza en el Shell el mensaje y el string

    chatter_pub.publish(exch); // Se publica msg acorde a los parametros dados en n.advertise

    ros::spinOnce();  // Revisa si le llego el dato a los suscriptores

    loop_rate.sleep(); // El programa duerme hasta cumplir 100ms  
    ++count;           // aumenta el contador
  }

  ros::spin(); //Realiza el bucle del subscriber, si se mata el modo publisher el codigo saltara aqui y el modo subscriber seguira funcionando hasta que el otro publisher se mate

  return 0;
}
