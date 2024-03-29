#include "pxt.h"
#include "pine.h"

enum class DigitalPin {
    P0 = 3,
    P1 = 2,
    P2 = 1,
    P3 = 4,
    P4 = 5,
    P5 = 17,
    P6 = 12,
    P7 = 11,
    P8 = 18,
    P9 = 10,
    P10 = 6,
    P11 = 26,
    P12 = 20,
    P13 = 23,
    P14 = 22,
    P15 = 21,
    P16 = 16,
    P19 = 0,
    P20 = 30
};

enum class AnalogPin {
    P0 = 3,
    P1 = 2,
    P2 = 1,
    P3 = 4,
    P4 = 5,
    P10 = 6,
    //% block="P5 (write only)"
    P5 = 17,
    //% block="P6 (write only)"
    P6 = 12,
    //% block="P7 (write only)"
    P7 = 11,
    //% block="P8 (write only)"
    P8 = 18,
    //% block="P9 (write only)"
    P9 = 10,
    //% block="P11 (write only)"
    P11 = 26,
    //% block="P12 (write only)"
    P12 = 20,
    //% block="P13 (write only)"
    P13 = 23,
    //% block="P14 (write only)"
    P14 = 22,
    //% block="P15 (write only)"
    P15 = 21,
    //% block="P16 (write only)"
    P16 = 16,
    //% block="P19 (write only)"
    P19 = 0,
    //% block="P20 (write only)"
    P20 = 30
};

enum class PulseValue {
    //% block=high
    High = DEVICE_PIN_EVT_PULSE_HI,
    //% block=low
    Low = DEVICE_PIN_EVT_PULSE_LO
};

enum class PinPullMode {
    //% block="down"
    PullDown = 0,
    //% block="up"
    PullUp = 1,
    //% block="none"
    PullNone = 2
};

enum class PinEventType {
    //% block="edge"
    Edge = DEVICE_PIN_EVENT_ON_EDGE,
    //% block="pulse"
    Pulse = DEVICE_PIN_EVENT_ON_PULSE,
    //% block="touch"
    Touch = DEVICE_PIN_EVENT_ON_TOUCH,
    //% block="none"
    None = DEVICE_PIN_EVENT_NONE
};


namespace pxt
{
DevicePin *getPin(int id) {
    switch (id) {
        case 3: return &uBit.io.P0;
        case 2: return &uBit.io.P1;
        case 1: return &uBit.io.P2;
        case 4: return &uBit.io.P3;
        case 5: return &uBit.io.P4;
        case 17: return &uBit.io.P5;
        case 12: return &uBit.io.P6;
        case 11: return &uBit.io.P7;
        case 18: return &uBit.io.P8;
        case 10: return &uBit.io.P9;
        case 6: return &uBit.io.P10;
        case 26: return &uBit.io.P11;
        case 20: return &uBit.io.P12;
        case 23: return &uBit.io.P13;
        case 22: return &uBit.io.P14;
        case 21: return &uBit.io.P15;
        case 16: return &uBit.io.P16;
        case 0: return &uBit.io.P19;
        case 30: return &uBit.io.P20;
        default: return NULL;
    }
}

} // pxt

namespace pine {
    #define PINOP(op) \
      DevicePin *pine = getPin((int)name); \
      if (!pine) return; \
      pine->op

    #define PINREAD(op) \
      DevicePin *pine = getPin((int)name); \
      if (!pine) return 0; \
      return pine->op


    //%
    DevicePin *getPinAddress(int id) {
        return getPin(id);
    }

    /**
     * Read the specified pin or connector as either 0 or 1
     * @param name pin to read from, eg: DigitalPin.P0
     */
    //% help=pins/digital-read-pin weight=30
    //% blockId=device_get_digital_pin block="digital read|pin %name" blockGap=8
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=4
    //% name.fieldOptions.tooltips="false" name.fieldOptions.width="250"
    int digitalReadPin(DigitalPin name) {
        PINREAD(getDigitalValue());
    }

    /**
      * Set a pin or connector value to either 0 or 1.
      * @param name pin to write to, eg: DigitalPin.P0
      * @param value value to set on the pin, 1 eg,0
      */
    //% help=pins/digital-write-pin weight=29
    //% blockId=device_set_digital_pin block="digital write|pin %name|to %value"
    //% value.min=0 value.max=1
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=4
    //% name.fieldOptions.tooltips="false" name.fieldOptions.width="250"
    void digitalWritePin(DigitalPin name, int value) {
        PINOP(setDigitalValue(value));
    }

    /**
     * Read the connector value as analog, that is, as a value comprised between 0 and 1023.
     * @param name pin to write to, eg: AnalogPin.P0
     */
    //% help=pins/analog-read-pin weight=25
    //% blockId=device_get_analog_pin block="analog read|pin %name" blockGap="8"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=4
    //% name.fieldOptions.tooltips="false" name.fieldOptions.width="250"
    int analogReadPin(AnalogPin name) {
        PINREAD(getAnalogValue());
    }

    /**
     * Set the connector value as analog. Value must be comprised between 0 and 1023.
     * @param name pin name to write to, eg: AnalogPin.P0
     * @param value value to write to the pin between ``0`` and ``1023``. eg:1023,0
     */
    //% help=pins/analog-write-pin weight=24
    //% blockId=device_set_analog_pin block="analog write|pin %name|to %value" blockGap=8
    //% value.min=0 value.max=1023
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=4
    //% name.fieldOptions.tooltips="false" name.fieldOptions.width="250"
    void analogWritePin(AnalogPin name, int value) {
        PINOP(setAnalogValue(value));
    }

    /**
     * Configure the pulse-width modulation (PWM) period of the analog output in microseconds.
     * If this pin is not configured as an analog output (using `analog write pin`), the operation has no effect.
     * @param name analog pin to set period to, eg: AnalogPin.P0
     * @param micros period in micro seconds. eg:20000
     */
    //% help=pins/analog-set-period weight=23 blockGap=8
    //% blockId=device_set_analog_period block="analog set period|pin %pin|to (µs)%micros"
    //% pin.fieldEditor="gridpicker" pin.fieldOptions.columns=4
    //% pin.fieldOptions.tooltips="false"
    void analogSetPeriod(AnalogPin name, int micros) {
        PINOP(setAnalogPeriodUs(micros));
    }

    /**
    * Configure the pin as a digital input and generate an event when the pin is pulsed either high or low.
    * @param name digital pin to register to, eg: DigitalPin.P0
    * @param pulse the value of the pulse, eg: PulseValue.High
    */
    //% help=pins/on-pulsed weight=22 blockGap=16 advanced=true
    //% blockId=pins_on_pulsed block="on|pin %pin|pulsed %pulse"
    //% pin.fieldEditor="gridpicker" pin.fieldOptions.columns=4
    //% pin.fieldOptions.tooltips="false" pin.fieldOptions.width="250"
    void onPulsed(DigitalPin name, PulseValue pulse, Action body) {
        DevicePin* pine = getPin((int)name);
        if (!pine) return;

        pine->eventOn(DEVICE_PIN_EVENT_ON_PULSE);
        registerWithDal((int)name, (int)pulse, body);
    }

    /**
    * Get the duration of the last pulse in microseconds. This function should be called from a ``onPulsed`` handler.
    */
    //% help=pins/pulse-duration advanced=true
    //% blockId=pins_pulse_duration block="pulse duration (µs)"
    //% weight=21 blockGap=8
    int pulseDuration() {
        return pxt::lastEvent.timestamp;
    }

    /**
    * Return the duration of a pulse at a pin in microseconds.
    * @param name the pin which measures the pulse, eg: DigitalPin.P0
    * @param value the value of the pulse, eg: PulseValue.High
    * @param maximum duration in microseconds
    */
    //% blockId="pins_pulse_in" block="pulse in (µs)|pin %name|pulsed %value"
    //% weight=20 advanced=true
    //% help=pins/pulse-in
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=4
    //% name.fieldOptions.tooltips="false" name.fieldOptions.width="250"
    int pulseIn(DigitalPin name, PulseValue value, int maxDuration = 2000000) {
        DevicePin* pine = getPin((int)name);
        if (!pine) return 0;

        int pulse = value == PulseValue::High ? 1 : 0;
        uint64_t tick =  system_timer_current_time_us();
        uint64_t maxd = (uint64_t)maxDuration;
        while(pine->getDigitalValue() != pulse) {
            if(system_timer_current_time_us() - tick > maxd)
                return 0;
        }

        uint64_t start =  system_timer_current_time_us();
        while(pine->getDigitalValue() == pulse) {
            if(system_timer_current_time_us() - tick > maxd)
                return 0;
        }
        uint64_t end =  system_timer_current_time_us();
        return end - start;
    }

    /**
     * Write a value to the servo, controlling the shaft accordingly. On a standard servo, this will set the angle of the shaft (in degrees), moving the shaft to that orientation. On a continuous rotation servo, this will set the speed of the servo (with ``0`` being full-speed in one direction, ``180`` being full speed in the other, and a value near ``90`` being no movement).
     * @param name pin to write to, eg: AnalogPin.P0
     * @param value angle or rotation speed, eg:180,90,0
     */
    //% help=pins/servo-write-pin weight=20
    //% blockId=device_set_servo_pin block="servo write|pin %name|to %value" blockGap=8
    //% parts=microservo trackArgs=0
    //% value.min=0 value.max=180
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=4
    //% name.fieldOptions.tooltips="false" name.fieldOptions.width="250"
    void servoWritePin(AnalogPin name, int value) {
        PINOP(setServoValue(value));
    }

    /**
     * Configure the IO pin as an analog/pwm output and set a pulse width. The period is 20 ms period and the pulse width is set based on the value given in **microseconds** or `1/1000` milliseconds.
     * @param name pin name
     * @param micros pulse duration in micro seconds, eg:1500
     */
    //% help=pins/servo-set-pulse weight=19
    //% blockId=device_set_servo_pulse block="servo set pulse|pin %value|to (µs) %micros"
    //% value.fieldEditor="gridpicker" value.fieldOptions.columns=4
    //% value.fieldOptions.tooltips="false" value.fieldOptions.width="250"
    void servoSetPulse(AnalogPin name, int micros) {
        PINOP(setServoPulseUs(micros));
    }


    DevicePin* pitchPin = NULL;

    /**
     * Set the pin used when using analog pitch or music.
     * @param name pin to modulate pitch from
     */
    //% blockId=device_analog_set_pitch_pin block="analog set pitch pin %name"
    //% help=pins/analog-set-pitch-pin weight=3 advanced=true
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=4
    //% name.fieldOptions.tooltips="false" name.fieldOptions.width="250"
    void analogSetPitchPin(AnalogPin name) {
      pitchPin = getPin((int)name);
    }

    /**
     * Emit a plse-width modulation (PWM) signal to the current pitch pin. Use `analog set pitch pin` to define the pitch pin.
     * @param frequency frequency to modulate in Hz.
     * @param ms duration of the pitch in milli seconds.
     */
    //% blockId=device_analog_pitch block="analog pitch %frequency|for (ms) %ms"
    //% help=pins/analog-pitch weight=4 async advanced=true blockGap=8
    void analogPitch(int frequency, int ms) {
      if (pitchPin == NULL)
        analogSetPitchPin(AnalogPin::P0);
      if (frequency <= 0) {
        pitchPin->setAnalogValue(0);
      } else {
        pitchPin->setAnalogValue(512);
        pitchPin->setAnalogPeriodUs(1000000/frequency);
      }

      if (ms > 0) {
          fiber_sleep(ms);
          pitchPin->setAnalogValue(0);
          // TODO why do we use wait_ms() here? it's a busy wait I think
          wait_ms(5);
      }
    }


    /**
    * Configure the pull directiion of of a pin.
    * @param name pin to set the pull mode on, eg: DigitalPin.P0
    * @param pull one of the mbed pull configurations, eg: PinPullMode.PullUp
    */
    //% help=pins/set-pull weight=3 advanced=true
    //% blockId=device_set_pull block="set pull|pin %pin|to %pull"
    //% pin.fieldEditor="gridpicker" pin.fieldOptions.columns=4
    //% pin.fieldOptions.tooltips="false" pin.fieldOptions.width="250"
    void setPull(DigitalPin name, PinPullMode pull) {
        PinMode m = pull == PinPullMode::PullDown
            ? PinMode::PullDown
            : pull == PinPullMode::PullUp ? PinMode::PullUp
            : PinMode::PullNone;
        PINOP(setPull(m));
    }

    /**
    * Configure the events emitted by this pin. Events can be subscribed to
    * using ``control.onEvent()``.
    * @param name pin to set the event mode on, eg: DigitalPin.P0
    * @param type the type of events for this pin to emit, eg: PinEventType.Edge
    */
    //% help=pins/set-events weight=4 advanced=true
    //% blockId=device_set_pin_events block="set pin %pin|to emit %type|events"
    //% pin.fieldEditor="gridpicker" pin.fieldOptions.columns=4
    //% pin.fieldOptions.tooltips="false" pin.fieldOptions.width="250"
    void setEvents(DigitalPin name, PinEventType type) {
        getPin((int)name)->eventOn((int)type);
    }

    /**
     * Create a new zero-initialized buffer.
     * @param size number of bytes in the buffer
     */
    //%
    Buffer createBuffer(int size)
    {
        return mkBuffer(NULL, size);
    }

    /**
     * Read `size` bytes from a 7-bit I2C `address`.
     */
    //%
    Buffer i2cReadBuffer(int address, int size, bool repeat = false)
    {
      Buffer buf = createBuffer(size);
      uBit.i2c.read(address << 1, (char*)buf->data, size, repeat);
      return buf;
    }

    /**
     * Write bytes to a 7-bit I2C `address`.
     */
    //%
    int i2cWriteBuffer(int address, Buffer buf, bool repeat = false)
    {
      return uBit.i2c.write(address << 1, (char*)buf->data, buf->length, repeat);
    }

    SPI* spi = NULL;
    SPI* allocSPI() {
        if (NULL == spi)
            spi = new SPI(MOSI, MISO, SCK);
        return spi;
    }

    /**
    * Write to the SPI slave and return the response
    * @param value Data to be sent to the SPI slave
    */
    //% help=pins/spi-write weight=5 advanced=true
    //% blockId=spi_write block="spi write %value"
    int spiWrite(int value) {
        auto p = allocSPI();
        return p->write(value);
    }

    /**
    * Set the SPI frequency
    * @param frequency the clock frequency, eg: 1000000
    */
    //% help=pins/spi-frequency weight=4 advanced=true
    //% blockId=spi_frequency block="spi frequency %frequency"
    void spiFrequency(int frequency) {
        auto p = allocSPI();
        p->frequency(frequency);
    }

    /**
    * Set the SPI bits and mode
    * @param bits the number of bits, eg: 8
    * @param mode the mode, eg: 3
    */
    //% help=pins/spi-format weight=3 advanced=true
    //% blockId=spi_format block="spi format|bits %bits|mode %mode"
    void spiFormat(int bits, int mode) {
        auto p = allocSPI();
        p->format(bits, mode);        
    }

    /**
    * Set the MOSI, MISO, SCK pins used by the SPI connection
    *
    */
    //% help=pins/spi-pins weight=2 advanced=true
    //% blockId=spi_pins block="spi set pins|MOSI %mosi|MISO %miso|SCK %sck"
    //% mosi.fieldEditor="gridpicker" mosi.fieldOptions.columns=4
    //% mosi.fieldOptions.tooltips="false" mosi.fieldOptions.width="250"
    //% miso.fieldEditor="gridpicker" miso.fieldOptions.columns=4
    //% miso.fieldOptions.tooltips="false" miso.fieldOptions.width="250"
    //% sck.fieldEditor="gridpicker" sck.fieldOptions.columns=4
    //% sck.fieldOptions.tooltips="false" sck.fieldOptions.width="250"
    void spiPins(DigitalPin mosi, DigitalPin miso, DigitalPin sck) {
        if (NULL != spi) {
            delete spi;
            spi = NULL;
        }

        spi = new SPI(getPin((int)mosi)->name, getPin((int)miso)->name, getPin((int)sck)->name);
    }
}
