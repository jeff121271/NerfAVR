/**
 *    pins.c
 *
 *    Handles logic for interacting with digital I/O pins.
 *
 *    Jeff Campbell
 *    2/13/18
 *
 */

/*
 *          Pin Assignments
 *  Pin     Port    Function        Description
 *  1       PA2     PA2             Heartbeat pin
 *  2       PD0
 *  3       PD1
 *  4       PA1
 *  5       PA0
 *  6       PD2
 *  7       PD3
 *  8       PD4
 *  9       PD5     OC0B            Flywheel PWM #2
 * 10       ---     Ground          Ground
 * 11       PD6
 * 12       PB0
 * 13       PB1
 * 14       PB2     OC0A            Flywheel PWM #1
 * 15       PB3
 * 16       PB4
 * 17       PB5
 * 18       PB6
 * 19       PB7
 * 20       ---     Vcc             Power supply
 *
 */

/* Includes */
#include <avr/io.h>
#include "pins.h"

/* Prototypes */
void gvPins_init(void);
static void vPins_configAll(void);
void gvPins_updateAll(void);
void gvPins_control(pin_index_t ePinIdx, uint8_t ubLogic);

/* Local Variables */

/* Array of pin descriptions */
static pin_desc_t digitalPins[PIN_NUMBER];

/**
 *    void gvPins_init(void)
 *
 *    Description:
 *        Initializes digital pin configurations.
 *
 *    Parameters:
 *        N/A
 *
 *    Returns:
 *        N/A
 *
 */
void gvPins_init(void)
{
    /* Heartbeat pin */
    digitalPins[PIN_HEARTBEAT].logicLevel = PIN_LOGIC_LOW;
    digitalPins[PIN_HEARTBEAT].direction = PIN_DIRECTION_OUTPUT;
    digitalPins[PIN_HEARTBEAT].portSel = PIN_SELECT_PORTA;
    digitalPins[PIN_HEARTBEAT].pullupEnable = PIN_PULLUP_DISABLE;
    digitalPins[PIN_HEARTBEAT].pinNum = 2u;

    /* Apply pin configurations */
    vPins_configAll();

    /* Update pins */
    gvPins_updateAll();
}

/**
 *    static void vPins_configAll(void)
 *
 *    Description:
 *        Configures all the pins' registers.
 *
 *    Parameters:
 *        N/A
 *
 *    Returns:
 *        N/A
 *
 */
static void vPins_configAll(void)
{
    pin_index_t ePinIdx;

    /* Loop over all pins */
    for ( ePinIdx = (pin_index_t)0u; ePinIdx < PIN_NUMBER; ePinIdx++ )
    {
        /* Process output pins */
        if ( PIN_DIRECTION_OUTPUT == digitalPins[ePinIdx].direction )
        {
            /* Select port */
            switch (digitalPins[ePinIdx].portSel)
            {
                case PIN_SELECT_PORTA:
                    DDRA |= (1u << digitalPins[ePinIdx].pinNum);
                    break;

                case PIN_SELECT_PORTB:
                    DDRB |= (1u << digitalPins[ePinIdx].pinNum);
                    break;

                case PIN_SELECT_PORTD:
                    DDRD |= (1u << digitalPins[ePinIdx].pinNum);
                    break;

                default:
                    /* Do nothing */
                    break;
            }
        }
        /* Process input pins */
        else
        {
            /* Select port */
            switch (digitalPins[ePinIdx].portSel)
            {
                case PIN_SELECT_PORTA:
                    DDRA &= (uint8_t)(~(1u << digitalPins[ePinIdx].pinNum));
                    break;

                case PIN_SELECT_PORTB:
                    DDRB &= (uint8_t)(~(1u << digitalPins[ePinIdx].pinNum));
                    break;

                case PIN_SELECT_PORTD:
                    DDRD &= (uint8_t)(~(1u << digitalPins[ePinIdx].pinNum));
                    break;

                default:
                    /* Do nothing */
                    break;
            }
        }
    }
}

/**
 *    void gvPins_updateAll(void)
 *
 *    Description:
 *        Updates the status of the pins.  Pushes all output pins to the Port
 *        registers and reads all input pins from the ports.
 *
 *    Parameters:
 *        N/A
 *
 *    Returns:
 *        N/A
 *
 */
void gvPins_updateAll(void)
{
    pin_index_t ePinIdx;

    /* Loop over each pin object */
    for ( ePinIdx = (pin_index_t)0u; ePinIdx < PIN_NUMBER; ePinIdx++ )
    {
        /* Process output pin */
        if ( PIN_DIRECTION_OUTPUT == digitalPins[ePinIdx].direction )
        {
            /* Select the appropriate port */
            switch (digitalPins[ePinIdx].portSel)
            {
                case PIN_SELECT_PORTA:
                    if ( PIN_LOGIC_LOW == digitalPins[ePinIdx].logicLevel )
                    {
                        PORTA &= (uint8_t)(~(1 << digitalPins[ePinIdx].pinNum));
                    }
                    else
                    {
                        PORTA |= (digitalPins[ePinIdx].logicLevel << digitalPins[ePinIdx].pinNum);
                    }
                    break;

                case PIN_SELECT_PORTB:
                    if ( PIN_LOGIC_LOW == digitalPins[ePinIdx].logicLevel )
                    {
                        PORTB &= (uint8_t)(~(1 << digitalPins[ePinIdx].pinNum));
                    }
                    else
                    {
                        PORTB |= (digitalPins[ePinIdx].logicLevel << digitalPins[ePinIdx].pinNum);
                    }
                    break;

                case PIN_SELECT_PORTD:
                    if ( PIN_LOGIC_LOW == digitalPins[ePinIdx].logicLevel )
                    {
                        PORTD &= (uint8_t)(~(1 << digitalPins[ePinIdx].pinNum));
                    }
                    else
                    {
                        PORTD |= (digitalPins[ePinIdx].logicLevel << digitalPins[ePinIdx].pinNum);
                    }
                    break;

                default:
                    /* Do nothing */
                    break;
            }
        }
        /* Process input pin */
        else
        {
            /* Select appropriate port */
            switch (digitalPins[ePinIdx].portSel)
            {
                case PIN_SELECT_PORTA:
                    digitalPins[ePinIdx].logicLevel = ((PORTA & (1u << digitalPins[ePinIdx].pinNum)) > 0) ? PIN_LOGIC_HIGH : PIN_LOGIC_LOW;
                    break;

                case PIN_SELECT_PORTB:
                    digitalPins[ePinIdx].logicLevel = ((PORTB & (1u << digitalPins[ePinIdx].pinNum)) > 0) ? PIN_LOGIC_HIGH : PIN_LOGIC_LOW;
                    break;

                case PIN_SELECT_PORTD:
                    digitalPins[ePinIdx].logicLevel = ((PORTD & (1u << digitalPins[ePinIdx].pinNum)) > 0) ? PIN_LOGIC_HIGH : PIN_LOGIC_LOW;
                    break;

                default:
                    /* Do nothing */
                    break;
            }
        }
    }
}

/**
 *    void gvPins_control(pin_index_t, uint8_t ubLogic)
 *
 *    Description:
 *        Sets the logic level of the selected pin.
 *
 *    Parameters:
 *        ePinIdx = Index of pin to change
 *        ubLogic = Logic level to use
 *
 *    Returns:
 *        N/A
 *
 */
void gvPins_control(pin_index_t ePinIdx, uint8_t ubLogic)
{
    /* Validate pin index */
    if ( ePinIdx < PIN_NUMBER )
    {
        /* Make sure pin is in output mode */
        if ( PIN_DIRECTION_OUTPUT == digitalPins[ePinIdx].direction )
        {
            /* Set pin level */
            digitalPins[ePinIdx].logicLevel = ubLogic;
        }
    }
}