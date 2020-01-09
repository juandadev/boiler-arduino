# Simulador de boiler eléctrico con Arduino UNO

Prototipo sencillo que simula un boiler eléctrico en el cual se ajustará el tiempo que permanecerá en funcionamiento en diferentes configuraciones.

## Funcionamiento
El sistema cuenta con tres configuraciones:

- Verano
- Invierno
- Apagado

Las cuales se pueden elegir mediante un potenciómetro. Las opciones serán mostradas en un display LCD así como en unos LEDs(3) que indicarán en cual configuracion que se encuentra actualmente.

Los LEDs son importantes ya que mediante su estado **HIGH** o **LOW** el código ejecuta las acciones correspondientes para cada configuración.

Existen dos botones, uno con el que se elegirá el *tiempo* y otro en el que se dará *incio* a la cuenta.

1. Al presionar el primer botón por default no pasará nada, este arrojará un aviso para seleccionar una configuración. Para que esto funcione se necesita dar vuelta al potenciómetro para elegir una configuración (que se enciendan los LEDs).
    - Tanto para el modo *Verano* e *Invierno* se podrá elegir entre 15, 20 y 25 segundos para fines prácticos, en la vida real se tendrían los mismos valroes pero en minutos.
    - De igual forma si se encuentra en modo *Apagado* volverá a avisar que se debe elegir una configuración válida.
2. Una vez establecido el tiempo se puede dar inicio a la cuenta regresiva presionando el segundo botón.
    - Si inicialmente se eligió la configuración pero no el tiempo, al presionar este botón arrojará un aviso para seleccionar el tiempo de calentamiento.
    - Si el tiempo ya ha sido elegido pero después se decide cambiar de configuración, el contador se reinicia y se tendrá que elegir de nuevo el tiempo.
Por último se cuentan con dos LEDs que indican el estado actual del boiler, siendo el de color **rojo** indicandor de que el boiler se encuentra apagado, y el **verde** cuando se inicia el timer. Una vez que la cuenta llega a 0 el LED rojo vuelve a prenderse indicando que el boiler está apagado nuevamente.

## Diagrama del circuito

![Diagrama circuito](https://github.com/Juandamartn/boiler-arduino/blob/master/diagrama.png)

Se puede ver con detalle el circuito y funcionamiento en Tinkercad [aquí][tinker]

[tinker]: https://www.tinkercad.com/things/bZsRw5WPWK4

## Video de funcionamiento

![Prototipo circuito](https://github.com/Juandamartn/boiler-arduino/blob/master/boiler%20arduino.jpg)

[Enlace al video][vid]

[vid]: https://drive.google.com/file/d/1C5zObRX8bwOxj7cgjiljcwaA5zwxyvLs/view?usp=sharing