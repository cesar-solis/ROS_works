#include "ros/ros.h"          //Libreria de ROS
#include "std_msgs/String.h"  //Libreria de datos tipo string

#include <sstream>             //Libreria String de C++

std_msgs::String valor_bool_rcv; // variable global

void chatterCallback(const std_msgs::String::ConstPtr& valor_bool) //Sub: Funcion chatterCallback el cual va a tomar a la variable valor_bool de tipo string del paquete std_msgs usando un puntero
{
    valor_bool_rcv.data = valor_bool->data; // Asigna el valor recibido a la variable global
    ROS_INFO("Recibi que el estado de la maquina es (%s) ", valor_bool->data.c_str()); //Sub: Imprime en el shell el texto y extrae el valor data de la variable valor_bool,la cual esta siendo 
    ROS_INFO("=================================================================="); // enviada por el nodo de arduino 
}

int main(int argc, char **argv)  //Funcion Principal
{

  ros::init(argc, argv, "sensor_bool_string"); //Inicializa el nodo de nombre sensor_bool_string
  ros::NodeHandle n; // Punto de acceso principal para comunicarse con el sistema ROS y tambien va a inicializar el nodo, se crea un objeto n de la clase NodeHandle

  ros::Subscriber sub = n.subscribe("topic_bool_to_string", 1000, chatterCallback); /* Sub: Le avisa al nodo maestro de ROS que se va a suscribir al topic "topic_bool_to_string" a traves de la 
  	funcion subscribe() de tipo NodeHandle. ROS llamara a la funcion chatterCallback cada vez que se recibe un mensaje 
  	* 1000 es el tamaño del buffer por si se pierde informacion  */

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("topic_bool_to_string_translate", 1000); /* Pub: Le avisa al nodo maestro de ROS que se va a publicar y còmo se va a 
  	publicar un mensaje de tipo string del paquete std_msgs a cualquier nodo suscrito al topic "topic_bool_to_string" a traves del publisher chatter_pub 
  	* 1000 es el tamaño del buffer por si se pierde informacion  */

  ros::Rate loop_rate(10); //Pub: Le da una frecuencia de muestreo de 10 mensajes por segundo o 100ms de actualizacion hasta que entre en sleep
  
  // -------------------------------------------- Modo Publisher ---------------------------------------------------------------------------------------
  while (ros::ok())   // Se usa un while con el condicional de que si ros esta operando se ejecuta el bucle, esto nos servira al querer matar la operacion con ctrl c 
  {                   // el cual hara que ros::ok() retorne un false y salga del bucle parando la publicacion. 
    std_msgs::String valor_bool_eng; // Se crea la variable que sera publicada
    std::stringstream ss; // se crea un objeto ss de tipo stringstream del paquete standard de c++

    if (valor_bool_rcv.data == "encendido")//Si el string recibido es identico a "encendido"
    {
        ss << "on"; // se le rellena el objeto ss con el mensaje on
        valor_bool_eng.data = ss.str(); // Se le asigna el stringstream creado a la variable valor_bool_eng el cual tiene estructura data ya que es un string
    }
    else
    {
        ss << "off"; // se le rellena el objeto ss con el mensaje off
        valor_bool_eng.data = ss.str(); // Se le asigna el stringstream creado a la variable valor_bool_eng el cual tiene estructura data ya que es un string
    }
    
    ROS_INFO("Sending machine result: (%s) ", valor_bool_eng.data.c_str()); // Visualiza en el Shell el mensaje y el string


    chatter_pub.publish(valor_bool_eng); // Se publica valor_bool_eng acorde a los parametros dados en n.advertise

    ros::spinOnce();  // Revisa si le llego el dato a los suscriptores

    loop_rate.sleep(); // El programa duerme hasta cumplir 100ms  
  }

  ros::spin(); //Realiza el bucle del subscriber, si se mata el modo publisher el codigo saltara aqui y el modo subscriber seguira funcionando hasta que el otro publisher se mate

  return 0;
}
