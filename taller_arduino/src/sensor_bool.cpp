#include "ros/ros.h"          //Libreria de ROS
#include "std_msgs/String.h"  //Libreria de datos tipo string
#include "std_msgs/Bool.h"   //Libreria de datos tipo bool

#include <sstream>             //Libreria String de C++

std_msgs::Bool on_off_rcv; // variable global

void chatterCallback(const std_msgs::Bool::ConstPtr& on_off) //Sub: Funcion chatterCallback el cual va a tomar a la variable on_off de tipo Bool del paquete std_msgs usando un puntero
{
    on_off_rcv.data = on_off->data; // Asigna el valor recibido a la variable global
    ROS_INFO("Estado de maquina recibido: (%s) ", on_off->data ? "1" : "0"); //Sub: Extrae el valor data de la variable on_off,la cual esta siendo enviada por el 
}										// nodo de arduino y si es true imprime 1, de lo contrario imprime 0 							

int main(int argc, char **argv)  //Funcion Principal
{

  ros::init(argc, argv, "sensor_bool"); //Inicializa el nodo de nombre sensor_bool
  ros::NodeHandle n; // Punto de acceso principal para comunicarse con el sistema ROS y tambien va a inicializar el nodo, se crea un objeto n de la clase NodeHandle

  ros::Subscriber sub = n.subscribe("topic_arduino_bool", 1000, chatterCallback); /* Sub: Le avisa al nodo maestro de ROS que se va a suscribir al topic "topic_arduino_bool" a traves de la 
  	funcion subscribe() de tipo NodeHandle. ROS llamara a la funcion chatterCallback cada vez que se recibe un mensaje 
  	* 1000 es el tamaño del buffer por si se pierde informacion  */

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("topic_bool_to_string", 1000); /* Pub: Le avisa al nodo maestro de ROS que se va a publicar y còmo se va a 
  	publicar un mensaje de tipo string del paquete std_msgs a cualquier nodo suscrito al topic "topic_bool_to_string" a traves del publisher chatter_pub 
  	* 1000 es el tamaño del buffer por si se pierde informacion  */

  ros::Rate loop_rate(10); //Pub: Le da una frecuencia de muestreo de 10 mensajes por segundo o 100ms de actualizacion hasta que entre en sleep
  
  // -------------------------------------------- Modo Publisher ---------------------------------------------------------------------------------------
  while (ros::ok())   // Se usa un while con el condicional de que si ros esta operando se ejecuta el bucle, esto nos servira al querer matar la operacion con ctrl c 
  {                   // el cual hara que ros::ok() retorne un false y salga del bucle parando la publicacion. 
    std_msgs::String valor_bool; // Se crea la variable que sera publicada
    std::stringstream ss; // se crea un objeto ss de tipo stringstream del paquete standard de c++

    if (on_off_rcv.data == true)//Si se recibe true o sea 1
    {
        ss << "encendido"; // se le rellena el objeto ss con el mensaje encendido
        valor_bool.data = ss.str(); // Se le asigna el stringstream creado a la variable valor_bool el cual tiene estructura data ya que es un string
    }
    else//si se recibe 0
    {
        ss << "apagado"; // se le rellena el objeto ss con el mensaje apagado
        valor_bool.data = ss.str(); // Se le asigna el stringstream creado a la variable valor_bool el cual tiene estructura data ya que es un string
    }
    
    ROS_INFO("La maquina se encuentra %s ", valor_bool.data.c_str()); // Visualiza en el Shell el mensaje y el string

    chatter_pub.publish(valor_bool); // Se publica valor_bool acorde a los parametros dados en n.advertise

    ros::spinOnce();  // Revisa si le llego el dato a los suscriptores

    loop_rate.sleep(); // El programa duerme hasta cumplir 100ms o 10Hz  
  }

  ros::spin(); //Realiza el bucle del subscriber, si se mata el modo publisher el codigo saltara aqui y el modo subscriber seguira funcionando hasta que el otro publisher se mate

  return 0;
}
