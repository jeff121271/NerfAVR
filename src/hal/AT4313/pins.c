/**
 *  pins.c
 *
 *  Handles logic for interacting with digital I/O pins.
 *
 *  Jeff Campbell
 *  2/13/18
 *
 */

/*
 *          Pin Assignments
 *  Pin     Port    Alt. Function   Description
 *  1       PA2     ---             Heartbeat pin
 *  2       PD0     ---             Dart-in-chamber photosensor
 *  3       PD1     ---             Push motor retracted photosensor
 *  4       PA1     ---             Push motor command #1
 *  5       PA0     ---             Push motor command #2
 *  6       PD2     INT0            Flywheel #1 feedback
 *  7       PD3     INT1            Flywheel #2 feedback
 *  8       PD4     ---             Trigger
 *  9       PD5     OC0B            Flywheel PWM #2
 * 10       GND     ---             Ground
 * 11       PD6     ---             Flywheel enable input
 * 12       PB0     ---             TM1637 Data pin
 * 13       PB1     ---             TM1637 Clock pin
 * 14       PB2     OC0A            Flywheel PWM #1
 * 15       PB3
 * 16       PB4
 * 17       PB5
 * 18       PB6
 * 19       PB7
 * 20       VCC     ---             Power supply
 *
 */

/* Includes */
#include <avr/io.h>
#include "pins.h"

/* Prototypes */
void gvPins_init(void);
static void vPins_configAll(void);
static void vPins_update(pin_index_t ePinIdx);
void gvPins_updateAll(void);
void gvPins_control(pin_index_t ePinIdx, uint8_t ubLogic);
void gvPins_toggle(pin_index_t ePinIdx);
uint8_t gubPins_read(pin_index_t ePinIdx);

/* Local Variables */

/* Array of pin descriptions */
static pin_desc_t digitalPins[PIN_COUNT];

/**
 *  void gvPins_init(void)
 *
 *  Description:
 *      Initializes digital pin configurations.
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      N/A
 *
 */
void gvPins_init(void)
{
    /* Heartbeat pin (PA2) */
    digitalPins[PIN_HEARTBEAT].logicLevel       = PIN_LOGIC_LOW;
    digitalPins[PIN_HEARTBEAT].direction        = PIN_DIRECTION_OUTPUT;
    digitalPins[PIN_HEARTBEAT].portSel          = PIN_SELECT_PORTA;
    digitalPins[PIN_HEARTBEAT].pullupEnable     = PIN_PULLUP_DISABLE;
    digitalPins[PIN_HEARTBEAT].pinNum           = 2u;

    /* Dart in chamber sensor (PD0) */
    digitalPins[PIN_DART_CHAMBER].logicLevel    = PIN_LOGIC_HIGH;
    digitalPins[PIN_DART_CHAMBER].direction     = PIN_DIRECTION_INPUT;
    digitalPins[PIN_DART_CHAMBER].portSel       = PIN_SELECT_PORTD;
    digitalPins[PIN_DART_CHAMBER].pullupEnable  = PIN_PULLUP_ENABLE;
    digitalPins[PIN_DART_CHAMBER].pinNum        = 0u;

    /* Push motor retracted sensor (PD1) */
    digitalPins[PIN_PUSH_RETRACTED].logicLevel      = PIN_LOGIC_HIGH;
    digitalPins[PIN_PUSH_RETRACTED].direction       = PIN_DIRECTION_INPUT;
    digitalPins[PIN_PUSH_RETRACTED].portSel         = PIN_SELECT_PORTD;
    digitalPins[PIN_PUSH_RETRACTED].pullupEnable    = PIN_PULLUP_ENABLE;
    digitalPins[PIN_PUSH_RETRACTED].pinNum          = 1u;

    /* Push motor command #1 (PA1) */
    digitalPins[PIN_PUSH_CMD_1].logicLevel      = PIN_LOGIC_LOW;
    digitalPins[PIN_PUSH_CMD_1].direction       = PIN_DIRECTION_OUTPUT;
    digitalPins[PIN_PUSH_CMD_1].portSel         = PIN_SELECT_PORTA;
    digitalPins[PIN_PUSH_CMD_1].pullupEnable    = PIN_PULLUP_DISABLE;
    digitalPins[PIN_PUSH_CMD_1].pinNum          = 1u;

    /* Push motor command #2 (PA0) */
    digitalPins[PIN_PUSH_CMD_2].logicLevel      = PIN_LOGIC_LOW;
    digitalPins[PIN_PUSH_CMD_2].direction       = PIN_DIRECTION_OUTPUT;
    digitalPins[PIN_PUSH_CMD_2].portSel         = PIN_SELECT_PORTA;
    digitalPins[PIN_PUSH_CMD_2].pullupEnable    = PIN_PULLUP_DISABLE;
    digitalPins[PIN_PUSH_CMD_2].pinNum          = 0u;

    /* Flywheel PWM #2 (PD5) */
    digitalPins[PIN_FLYWHEEL_PWM_2].logicLevel      = PIN_LOGIC_LOW;
    digitalPins[PIN_FLYWHEEL_PWM_2].direction       = PIN_DIRECTION_OUTPUT;
    digitalPins[PIN_FLYWHEEL_PWM_2].portSel         = PIN_SELECT_PORTD;
    digitalPins[PIN_FLYWHEEL_PWM_2].pullupEnable    = PIN_PULLUP_DISABLE;
    digitalPins[PIN_FLYWHEEL_PWM_2].pinNum          = 5u;

    /* Flywheel PWM #1 (PB2) */
    digitalPins[PIN_FLYWHEEL_PWM_1].logicLevel      = PIN_LOGIC_LOW;
    digitalPins[PIN_FLYWHEEL_PWM_1].direction       = PIN_DIRECTION_OUTPUT;
    digitalPins[PIN_FLYWHEEL_PWM_1].portSel         = PIN_SELECT_PORTB;
    digitalPins[PIN_FLYWHEEL_PWM_1].pullupEnable    = PIN_PULLUP_DISABLE;
    digitalPins[PIN_FLYWHEEL_PWM_1].pinNum          = 2u;

    /* Flywheel #1 feedback (PD2) */
    digitalPins[PIN_FLYWHEEL_FB_1].logicLevel       = PIN_LOGIC_LOW;
    digitalPins[PIN_FLYWHEEL_FB_1].direction        = PIN_DIRECTION_INPUT;
    digitalPins[PIN_FLYWHEEL_FB_1].portSel          = PIN_SELECT_PORTD;
    digitalPins[PIN_FLYWHEEL_FB_1].pullupEnable     = PIN_PULLUP_ENABLE;
    digitalPins[PIN_FLYWHEEL_FB_1].pinNum           = 2u;

    /* Flywheel #2 feedback (PD3) */
    digitalPins[PIN_FLYWHEEL_FB_2].logicLevel       = PIN_LOGIC_LOW;
    digitalPins[PIN_FLYWHEEL_FB_2].direction        = PIN_DIRECTION_INPUT;
    digitalPins[PIN_FLYWHEEL_FB_2].portSel          = PIN_SELECT_PORTD;
    digitalPins[PIN_FLYWHEEL_FB_2].pullupEnable     = PIN_PULLUP_ENABLE;
    digitalPins[PIN_FLYWHEEL_FB_2].pinNum           = 3u;

    /* Trigger input (PD4) */
    digitalPins[PIN_TRIGGER].logicLevel     = PIN_LOGIC_LOW;
    digitalPins[PIN_TRIGGER].direction      = PIN_DIRECTION_INPUT;
    digitalPins[PIN_TRIGGER].portSel        = PIN_SELECT_PORTD;
    digitalPins[PIN_TRIGGER].pullupEnable   = PIN_PULLUP_DISABLE;
    digitalPins[PIN_TRIGGER].pinNum         = 4u;

    /* Flywheel enable input (PD6) */
    digitalPins[PIN_WHEEL_CMD].logicLevel   = PIN_LOGIC_LOW;
    digitalPins[PIN_WHEEL_CMD].direction    = PIN_DIRECTION_INPUT;
    digitalPins[PIN_WHEEL_CMD].portSel      = PIN_SELECT_PORTD;
    digitalPins[PIN_WHEEL_CMD].pullupEnable = PIN_PULLUP_DISABLE;
    digitalPins[PIN_WHEEL_CMD].pinNum       = 6u;

    /* Apply pin configurations */
    vPins_configAll();

    /* Update pins */
    gvPins_updateAll();
}

/**
 *  static void vPins_configAll(void)
 *
 *  Description:
 *      Configures all the pins' registers.
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      N/A
 *
 */
static void vPins_configAll(void)
{
    pin_index_t ePinIdx;

    /* Loop over all pins */
    for ( ePinIdx = (pin_index_t)0u; ePinIdx < PIN_COUNT; ePinIdx++ )
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
                    if ( PIN_PULLUP_ENABLE == digitalPins[ePinIdx].pullupEnable )
                    {
                        PORTA |= (1u << digitalPins[ePinIdx].pinNum);
                    }
                    break;

                case PIN_SELECT_PORTB:
                    DDRB &= (uint8_t)(~(1u << digitalPins[ePinIdx].pinNum));
                    if ( PIN_PULLUP_ENABLE == digitalPins[ePinIdx].pullupEnable )
                    {
                        PORTB |= (1u << digitalPins[ePinIdx].pinNum);
                    }
                    break;

                case PIN_SELECT_PORTD:
                    DDRD &= (uint8_t)(~(1u << digitalPins[ePinIdx].pinNum));
                    if ( PIN_PULLUP_ENABLE == digitalPins[ePinIdx].pullupEnable )
                    {
                        PORTD |= (1u << digitalPins[ePinIdx].pinNum);
                    }
                    break;

                default:
                    /* Do nothing */
                    break;
            }
        }
    }
}

/**
 *  static void vPins_update(pin_index_t ePinIdx)
 *
 *  Description:
 *      Updates the status of a single pin.
 *
 *  Parameters:
 *      ePinIdx = Index of the pin to update
 *
 *  Returns:
 *      N/A
 *
 */
static void vPins_update(pin_index_t ePinIdx)
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
                digitalPins[ePinIdx].logicLevel = ((PINA & (1u << digitalPins[ePinIdx].pinNum)) > 0) ? PIN_LOGIC_HIGH : PIN_LOGIC_LOW;
                break;

            case PIN_SELECT_PORTB:
                digitalPins[ePinIdx].logicLevel = ((PINB & (1u << digitalPins[ePinIdx].pinNum)) > 0) ? PIN_LOGIC_HIGH : PIN_LOGIC_LOW;
                break;

            case PIN_SELECT_PORTD:
                digitalPins[ePinIdx].logicLevel = ((PIND & (1u << digitalPins[ePinIdx].pinNum)) > 0) ? PIN_LOGIC_HIGH : PIN_LOGIC_LOW;
                break;

            default:
                /* Do nothing */
                break;
        }
    }
}

/**
 *  void gvPins_updateAll(void)
 *
 *  Description:
 *      Updates the status of the pins.  Pushes all output pins to the Port
 *      registers and reads all input pins from the ports.
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      N/A
 *
 */
void gvPins_updateAll(void)
{
    pin_index_t ePinIdx;

    /* Loop over each pin object */
    for ( ePinIdx = (pin_index_t)0u; ePinIdx < PIN_COUNT; ePinIdx++ )
    {
        /* Update the pin */
        vPins_update(ePinIdx);
    }
}

/**
 *  void gvPins_control(pin_index_t, uint8_t ubLogic)
 *
 *  Description:
 *      Sets the logic level of the selected pin.
 *
 *  Parameters:
 *      ePinIdx = Index of pin to change
 *      ubLogic = Logic level to use
 *
 *  Returns:
 *      N/A
 *
 */
void gvPins_control(pin_index_t ePinIdx, uint8_t ubLogic)
{
    /* Validate pin index */
    if ( ePinIdx < PIN_COUNT )
    {
        /* Make sure pin is in output mode */
        if ( PIN_DIRECTION_OUTPUT == digitalPins[ePinIdx].direction )
        {
            /* Set pin level */
            digitalPins[ePinIdx].logicLevel = ubLogic;

            /* Update pin */
            vPins_update(ePinIdx);
        }
    }
}

/**
 *  void gvPins_toggle(pin_index_t ePinIdx)
 *
 *  Description:
 *      Toggles the selected output pin.
 *
 *  Parameters:
 *      ePinIdx = Pin to toggle
 *
 *  Returns:
 *      N/A
 *
 */
void gvPins_toggle(pin_index_t ePinIdx)
{
    /* Validate pin index */
    if ( ePinIdx < PIN_COUNT )
    {
        /* Make sure pin is in output mode */
        if ( PIN_DIRECTION_OUTPUT == digitalPins[ePinIdx].direction )
        {
            /* Write to the appropriate PIN register */
            switch (digitalPins[ePinIdx].portSel)
            {
                case PIN_SELECT_PORTA:
                    PINA |= 1u << digitalPins[ePinIdx].pinNum;
                    break;

                case PIN_SELECT_PORTB:
                    PINB |= 1u << digitalPins[ePinIdx].pinNum;
                    break;

                case PIN_SELECT_PORTD:
                    PIND |= 1u << digitalPins[ePinIdx].pinNum;
                    break;

                default:
                    /* Do nothing */
                    break;
            }
        }

        /* Toggle logic status in structure */
        if ( PIN_LOGIC_HIGH == digitalPins[ePinIdx].logicLevel )
        {
            digitalPins[ePinIdx].logicLevel = PIN_LOGIC_LOW;
        }
        else
        {
            digitalPins[ePinIdx].logicLevel = PIN_LOGIC_HIGH;
        }
    }
}

/**
 *  uint8_t gubPins_read(pin_index_t ePinIdx)
 *
 *  Description:
 *      Reads the current logic level of a pin.
 *
 *  Parameters:
 *      ePinIdx = Pin to read
 *
 *  Returns:
 *      The logic level of the pin.
 *
 */
uint8_t gubPins_read(pin_index_t ePinIdx)
{
    uint8_t ubLevel = 0xFFu;

    /* Validate pin index */
    if ( ePinIdx < PIN_COUNT )
    {
        /* Validate pin is in input mode */
        if ( PIN_DIRECTION_INPUT == digitalPins[ePinIdx].direction )
        {
            /* Update pin */
            vPins_update(ePinIdx);

            /* Read pin level */
            ubLevel = digitalPins[ePinIdx].logicLevel;
        }
    }

    /* Return result */
    return ubLevel;
}