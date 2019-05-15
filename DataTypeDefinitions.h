/*
 * DataTypeDefinitions.h
 *
 *  Created on: 11/08/2017
 *      Author: jlpe
 */

#ifndef DATATYPEDEFINITIONS_H_
#define DATATYPEDEFINITIONS_H_
typedef enum {
	FTM_0,
	FTM_1,
	FTM_2,
	FTM_3
}FTM_number;

typedef enum{
	MOTOR_0,
	MOTOR_1,
	MOTOR_2,
	MOTOR_3,
	MOTOR_4,
	MOTOR_5,
	MOTOR_6,
	MOTOR_7,
	MOTOR_8,
	MOTOR_9,
	MOTOR_10,
	MOTOR_11,
	MOTOR_12

}MOTOR_number;

typedef enum {
	PATA_1,
	PATA_2,
	PATA_3,
	PATA_4
}PATA_number;

typedef enum {
	ADELANTE,  // EXTREMIDAD 2 Y 3
	ATRAS		// EXTREMIDAD 1 Y 4
}diagonal_respecto_2;




typedef enum {
	FTM_CH0,
	FTM_CH1,
	FTM_CH2,
	FTM_CH3,
	FTM_CH4,
	FTM_CH5,
	FTM_CH6,
	FTM_CH7
}FTM_canal;

/*! This definition is as a general definitions to bits in regiter or pins in the microcontroller.*/
typedef enum {BIT0,  /*!< Bit 0 */
			  BIT1,  /*!< Bit 1 */
			  BIT2,  /*!< Bit 2 */
			  BIT3,  /*!< Bit 3 */
			  BIT4,  /*!< Bit 4 */
			  BIT5,  /*!< Bit 5 */
			  BIT6,  /*!< Bit 6 */
			  BIT7,  /*!< Bit 7 */
	          BIT8,  /*!< Bit 8 */
	          BIT9,  /*!< Bit 9 */
	          BIT10, /*!< Bit 10 */
	          BIT11, /*!< Bit 11 */
	          BIT12, /*!< Bit 12 */
	          BIT13, /*!< Bit 13 */
	          BIT14, /*!< Bit 14 */
	          BIT15, /*!< Bit 15 */
	          BIT16, /*!< Bit 16 */
	          BIT17, /*!< Bit 17 */
	          BIT18, /*!< Bit 18 */
	          BIT19, /*!< Bit 19 */
	          BIT20, /*!< Bit 20 */
	          BIT21, /*!< Bit 21 */
	          BIT22, /*!< Bit 22 */
	          BIT23,/*!< Bit 23 */
	          BIT24, /*!< Bit 24 */
	          BIT25, /*!< Bit 25 */
	          BIT26, /*!< Bit 26 */
	          BIT27, /*!< Bit 27 */
	          BIT28, /*!< Bit 28 */
	          BIT29, /*!< Bit 29 */
	          BIT30, /*!< Bit 30 */
	          BIT31  /*!< Bit 31 */
			} BitsType;


typedef enum{FALSE, TRUE} BooleanType;
/*! This definition is as a general definitions to bits turn-on or turn-off any bit*/
typedef enum {BIT_OFF, BIT_ON} BIT_ON_OFF_Type;
/*! This data type is unsigned integer of 8 bits*/
typedef unsigned char uint8;
/*! This data type is signed integer of 8 bits*/
typedef char sint8;
/*! This data type is 16-bit unsigned integer*/
typedef unsigned short int uint16;
/*! This data type is 16-bit signed integer*/
typedef short int sint16;
/*! This data type is 32-bit unsigned integer*/
typedef unsigned long int uint32;
/*! This data type is 16-bit signed integer*/
typedef long int sint32;
typedef float float32;

typedef struct servo {
	uint8 FTM;
	uint8 canal;
	float32 posicion_en_milisegundos;
	float32 PWM_max_limit;
	float32 PWM_min_limit;
}servo;


typedef struct extremidad {
	uint8 NumeroPata;
	servo servo_1;
	servo servo_2;
	servo servo_3;
	uint8 direccion;


}extremidad;

typedef struct arania{
	extremidad extremidad_1;
	extremidad extremidad_2;
	extremidad extremidad_3;
	extremidad extremidad_4;
}arania;



typedef enum {I2C_0, I2C_1, I2C_2}I2C_ChannelType;

 enum{SLAVE,MASTER};
 enum{RX,TX};

 /*Configuarcion para la I2C*/
typedef struct I2C_configuration  {
		I2C_ChannelType channel;
		uint32 systemClock;
		uint32 baudRate;
		uint8 MasterOrSlave;
		uint8 TxOrRx;
		uint8 WriteInstruction;
		uint8 ReadInstruction;
}I2C_configurationType;

#endif /* DATATYPEDEFINITIONS_H_ */
