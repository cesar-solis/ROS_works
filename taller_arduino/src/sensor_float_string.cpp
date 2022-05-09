#include "ros/ros.h"          //Libreria de ROS
#include "std_msgs/String.h"  //Libreria de datos tipo string

#include <sstream>             //Libreria String de C++

std_msgs::String valor_float_rcv;// variable global

void chatterCallback(const std_msgs::String::ConstPtr& valor_float) //Sub: Funcion chatterCallback el cual va a tomar a la variable valor_float de tipo string del paquete std_msgs usando un puntero
{
    valor_float_rcv.data = valor_float->data;// Asigna el valor recibido a la variable global
    ROS_INFO("Recibi que la velocidad es (%s) ", valor_float->data.c_str()); //Sub: Imprime en el shell el texto y extrae el valor data de la variable msg1,la cual esta siendo enviada por el 
    ROS_INFO("==================================================================");// nodo de arduino 
}		

int main(int argc, char **argv)  //Funcion Principal
{

  ros::init(argc, argv, "sensor_float_string"); //Inicializa el nodo de nombre sensor_float_string
  ros::NodeHandle n; // Punto de acceso principal para comunicarse con el sistema ROS y tambien va a inicializar el nodo, se crea un objeto n de la clase NodeHandle

  ros::Subscriber sub = n.subscribe("topic_float_to_string", 1000, chatterCallback); /* Sub: Le avisa al nodo maestro de ROS que se va a suscribir al topic "topic_float_to_string" a traves de la 
  	funcion subscribe() de tipo NodeHandle. ROS llamara a la funcion chatterCallback cada vez que se recibe un mensaje 
  	* 1000 es el tamaño del buffer por si se pierde informacion  */

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("topic_float_to_string_translate", 1000); /* Pub: Le avisa al nodo maestro de ROS que se va a publicar y còmo se va a 
  	publicar un mensaje de tipo string del paquete std_msgs a cualquier nodo suscrito al topic "topic_float_to_string_translate" a traves del publisher chatter_pub 
  	* 1000 es el tamaño del buffer por si se pierde informacion  */

  ros::Rate loop_rate(10); //Pub: Le da una frecuencia de muestreo de 10 mensajes por segundo o 100ms de actualizacion hasta que entre en sleep
  
  // -------------------------------------------- Modo Publisher ---------------------------------------------------------------------------------------
  while (ros::ok())   // Se usa un while con el condicional de que si ros esta operando se ejecuta el bucle, esto nos servira al querer matar la operacion con ctrl c 
  {                   // el cual hara que ros::ok() retorne un false y salga del bucle parando la publicacion. 
    std_msgs::String valor_float_eng; // Se crea la variable que sera publicada
    std::stringstream ss; // se crea un objeto ss de tipo stringstream del paquete standard de c++

    if (valor_float_rcv.data == "lento")//Si el string recibido es identico a "lento"
    {
        ss << "slow"; // se le rellena el objeto ss con el mensaje slow
        valor_float_eng.data = ss.str(); // Se le asigna el stringstream creado a la variable valor_float_eng el cual tiene estructura data ya que es un string
    }
    if (valor_float_rcv.data == "normal")//Si el string recibido es identico a "normal"
    {
        ss << "normal"; // se le rellena el objeto ss con el mensaje normal
        valor_float_eng.data = ss.str(); // Se le asigna el stringstream creado a la variable valor_float_eng el cual tiene estructura data ya que es un string
    }
    if (valor_float_rcv.data == "rapido")//Si el string recibido es identico a "rapido"
    {
        ss << "fast"; // se le rellena el objeto ss con el mensaje fast
        valor_float_eng.data = ss.str(); // Se le asigna el stringstream creado a la variable valor_float_eng el cual tiene estructura data ya que es un string
    }
    
    ROS_INFO("Sending speed result: (%s) ", valor_float_eng.data.c_str()); // Visualiza en el Shell el mensaje y el string

    chatter_pub.publish(valor_float_eng); // Se publica valor_float_eng acorde a los parametros dados en n.advertise

    ros::spinOnce();  // Revisa si le llego el dato a los suscriptores

    loop_rate.sleep(); // El programa duerme hasta cumplir 100ms  
  }

  ros::spin(); //Realiza el bucle del subscriber, si se mata el modo publisher el codigo saltara aqui y el modo subscriber seguira funcionando hasta que el otro publisher se mate

  return 0;
}
