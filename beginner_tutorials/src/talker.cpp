#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream> // leer y escribir strings

/**
 * mostrar el envio simple de mensajes a traves del sistema de ROS.
 */
int main(int argc, char **argv)
{
  /**
   * la funcion ros::init() necesita de argc y argv para realizar cualquier argumento de 
   * ROS y remapear nombres que se dieron en la linea de comandos.
   * Se pueden usar diferentes versiones de init() para los remaps lo cual requiere remapear
   * directamente, pero pasar argc y argv son las mas facil para la mayoria de programas
   * en lineas de comando. el tercer parametro es el nombre del nodo
   *
   * Siempre se debe llamar a la funcion ros::init() antes de usar cualquier otra 
   * parte del sistema de ROS
   */
  ros::init(argc, argv, "talker"); // nodo nombre talker, :: buscar en la libreria de ros la funcion init

  /**
   * NodeHandle es el punto de acceso principal para comunicarse con el sistema ROS().
   * El primer nodehandle va a inicializar completamente el nodo, mientras que el ultimo
   * nodehandle va a destruir el nodo.
   */
  ros::NodeHandle n; // crear objeto de la clase handle de la libreria ros de nombre n

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000); /* ir a nodehandle que tiene una funcion advertise, garantiza
  que se publique un string. 1000 buffer por si se pierde información. chatter_pub es el publicador*/

  ros::Rate loop_rate(10);// freq 10 hz clase rate funcion loop_rate

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok())//mientras ros este operando, al dar ctrl c eso se vuelve falso y sale
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg; 

    std::stringstream ss;
    ss << "hello world " << count; // muestra hello world e imprime count el cual incrementa cada 100 ms
    msg.data = ss.str(); /* tomar data y la colocamos en formato string, los puntos indican la estructura del tipo de dato
    en este caso msg es string y data es una estructura. Se googlea para ver la estructura */

    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    chatter_pub.publish(msg); // publicar msg el cual es std_msgs::String

    ros::spinOnce(); // spinonce revisa si ha llegado algo a los subscriptores

    loop_rate.sleep(); // duerma hasta que se completen los 10Hz <> 100ms 
    ++count; // incrementa count
  }


  return 0;
}
