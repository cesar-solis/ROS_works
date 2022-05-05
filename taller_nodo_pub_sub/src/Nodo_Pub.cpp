#include "ros/ros.h"                //Libreria de ROS
#include "std_msgs/String.h"	     //Libreria que incluye datos string del paquete std_msgs

#include <sstream> 		     //Libreria para manipular datos string de c++

int main(int argc, char **argv) // Funcion principal
{
  
  ros::init(argc, argv, "Nodo_Pub"); // Usamos la funcion inir de la libreria ROS y nombramos el nodo como Nodo_Pub
  ros::NodeHandle n; // Punto de acceso principal para comunicarse con el sistema ROS y tambien va a inicializar el nodo, se crea un objeto n de la clase NodeHandle

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("T_Pub_to_Sub_Pub", 1000); /* Le avisa al nodo maestro de ROS que se va a publicar y còmo se va a 
  	publicar un mensaje de tipo string del paquete std_msgs a cualquier nodo suscrito al topic "T_Pub_to_Sub_Pub" a traves del publisher chatter_pub 
  	* 1000 es el tamaño del buffer por si se pierde informacion  */
    
  ros::Rate loop_rate(10); //Le da una frecuencia de muestreo de 10 mensajes por segundo o 100ms de actualizacion hasta que entre en sleep
  
  int count = 0;// Se le agrega un contador que llevara la cuenta de mensajes enviados
    while (ros::ok()) // Se usa un while con el condicional de que si ros esta operando se ejecuta el bucle, esto nos servira al querer matar la operacion con ctrl c 
  {                   // el cual hara que ros::ok() retorne un false y salga del bucle parando la publicacion. 
    
    std_msgs::String msg1; // se crea un objeto msg1 de tipo String del paquete std_msgs

    std::stringstream ss; // se crea un objeto ss de tipo stringstream del paquete standard de c++
    ss << "Desarrollo " << count; // se le rellena el objeto ss con el dato deseado
    msg1.data = ss.str(); // Se le asigna el stringstream creado al objeto msg1 el cual tiene estructura data ya que es un string

    ROS_INFO("Enviando al nodo Sub_Pub: (%s) ", msg1.data.c_str()); // Visualiza en el Shell el mensaje y el string

    chatter_pub.publish(msg1); // Se publica msg1 acorde a los parametros dados en n.advertise

    ros::spinOnce();         // Revisa si le llego el dato a los suscriptores
    loop_rate.sleep();       // El programa duerme hasta cumplir 100ms  	
    ++count;                 // aumenta el contador
  }


  return 0;
}
