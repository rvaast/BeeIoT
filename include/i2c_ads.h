//*******************************************************************
// i2c_ads.h
// from Project https://github.com/mchresse/BeeIoT
//
// Description:
// ADS11x5 I2C related parameter file
//
//----------------------------------------------------------
// Copyright (c) 2019-present, Randolph Esser
// All rights reserved.
// This file is distributed under the BSD-3-Clause License
// The complete license agreement can be obtained at:
//     https://github.com/mchresse/BeeIoT/license
// For used 3rd party open source see also Readme_OpenSource.txt
//*******************************************************************
#ifndef I2C_ADS_H
#define I2C_ADS_H

#ifdef __cplusplus
extern "C" {
#endif

#define ADS111X_MAX_VALUE 0x7fff //!< Maximum ADC value
#define ADS101X_MAX_VALUE 0x7ff

// ADS101X overrides
#define ADS101X_DATA_RATE_128  	ADS111X_DATA_RATE_8
#define ADS101X_DATA_RATE_250  	ADS111X_DATA_RATE_16
#define ADS101X_DATA_RATE_490  	ADS111X_DATA_RATE_32
#define ADS101X_DATA_RATE_920  	ADS111X_DATA_RATE_64
#define ADS101X_DATA_RATE_1600	ADS111X_DATA_RATE_128
#define ADS101X_DATA_RATE_2400	ADS111X_DATA_RATE_250
#define ADS101X_DATA_RATE_3300	ADS111X_DATA_RATE_475

#define REG_CONVERSION 0
#define REG_CONFIG     1
#define REG_THRESH_L   2
#define REG_THRESH_H   3
#define COMP_QUE_OFFSET  1
#define COMP_QUE_MASK    0x03
#define COMP_LAT_OFFSET  2
#define COMP_LAT_MASK    0x01
#define COMP_POL_OFFSET  3
#define COMP_POL_MASK    0x01
#define COMP_MODE_OFFSET 4
#define COMP_MODE_MASK   0x01
#define DR_OFFSET        5
#define DR_MASK          0x07
#define MODE_OFFSET      8
#define MODE_MASK        0x01
#define PGA_OFFSET       9
#define PGA_MASK         0x07
#define MUX_OFFSET       12
#define MUX_MASK         0x07
#define OS_OFFSET      15
#define OS_MASK        0x01

/**
 * Gain amplifier
 */
typedef enum
{
    ADS111X_GAIN_6V144 = 0, //!< +-6.144V
    ADS111X_GAIN_4V096,     //!< +-4.096V
    ADS111X_GAIN_2V048,     //!< +-2.048V (default)
    ADS111X_GAIN_1V024,     //!< +-1.024V
    ADS111X_GAIN_0V512,     //!< +-0.512V
    ADS111X_GAIN_0V256,     //!< +-0.256V
    ADS111X_GAIN_0V256_2,   //!< +-0.256V (same as ADS111X_GAIN_0V256)
    ADS111X_GAIN_0V256_3,   //!< +-0.256V (same as ADS111X_GAIN_0V256)
} ads111x_gain_t;

extern const float ads111x_gain_values[];	// Gain amplifier values

/**
 * Input multiplexer configuration (ADS1115 only)
 */
typedef enum
{
    ADS111X_MUX_0_1 = 0, //!< positive = AIN0, negative = AIN1 (default)
    ADS111X_MUX_0_3,     //!< positive = AIN0, negative = AIN3
    ADS111X_MUX_1_3,     //!< positive = AIN1, negative = AIN3
    ADS111X_MUX_2_3,     //!< positive = AIN2, negative = AIN3
    ADS111X_MUX_0_GND,   //!< positive = AIN0, negative = GND
    ADS111X_MUX_1_GND,   //!< positive = AIN1, negative = GND
    ADS111X_MUX_2_GND,   //!< positive = AIN2, negative = GND
    ADS111X_MUX_3_GND,   //!< positive = AIN3, negative = GND
} ads111x_mux_t;

/**
 * Data rate
 */
typedef enum
{
    ADS111X_DATA_RATE_8 = 0, //!< 8 samples per second
    ADS111X_DATA_RATE_16,    //!< 16 samples per second
    ADS111X_DATA_RATE_32,    //!< 32 samples per second
    ADS111X_DATA_RATE_64,    //!< 64 samples per second
    ADS111X_DATA_RATE_128,   //!< 128 samples per second (default)
    ADS111X_DATA_RATE_250,   //!< 250 samples per second
    ADS111X_DATA_RATE_475,   //!< 475 samples per second
    ADS111X_DATA_RATE_860    //!< 860 samples per second
} ads111x_data_rate_t;

/**
 * Operational mode
 */
typedef enum
{
    ADS111X_MODE_CONTINUOS = 0, //!< Continuous conversion mode
    ADS111X_MODE_SINGLE_SHOT    //!< Power-down single-shot mode (default)
} ads111x_mode_t;

/**
 * Comparator mode (ADS1114 and ADS1115 only)
 */
typedef enum
{
    ADS111X_COMP_MODE_NORMAL = 0, //!< Traditional comparator with hysteresis (default)
    ADS111X_COMP_MODE_WINDOW      //!< Window comparator
} ads111x_comp_mode_t;

/**
 * Comparator polarity (ADS1114 and ADS1115 only)
 */
typedef enum
{
    ADS111X_COMP_POLARITY_LOW = 0, //!< Active low (default)
    ADS111X_COMP_POLARITY_HIGH     //!< Active high
} ads111x_comp_polarity_t;

/**
 * Comparator latch (ADS1114 and ADS1115 only)
 */
typedef enum
{
    ADS111X_COMP_LATCH_DISABLED = 0, //!< Non-latching comparator (default)
    ADS111X_COMP_LATCH_ENABLED       //!< Latching comparator
} ads111x_comp_latch_t;

/**
 * Comparator queue
 */
typedef enum
{
    ADS111X_COMP_QUEUE_1 = 0,   //!< Assert ALERT/RDY pin after one conversion
    ADS111X_COMP_QUEUE_2,       //!< Assert ALERT/RDY pin after two conversions
    ADS111X_COMP_QUEUE_4,       //!< Assert ALERT/RDY pin after four conversions
    ADS111X_COMP_QUEUE_DISABLED //!< Disable comparator (default)
} ads111x_comp_queue_t;


//***********************************************************************************
// Function prototypes
//
//***********************************************************************************
/*
 * Initialize device descriptior
 * @param dev Device descriptor
 * @param addr Device address
 * @param port I2C port number
 * @param sda_gpio GPIO pin for SDA
 * @param scl_gpio GPIO pin for SCL
 * @return `ESP_OK` on success
 */


esp_err_t ads111x_init_desc(i2c_dev_t *dev, uint8_t addr, i2c_port_t port,
        gpio_num_t sda_gpio, gpio_num_t scl_gpio);

/**
 * @brief Free device descriptor
 * @param dev Pointer to device descriptor
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_free_desc(i2c_dev_t *dev);

/**
 * Get device operational status
 * @param dev Device descriptor
 * @param busy `true` when device performing conversion
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_is_busy(i2c_dev_t *dev, bool *busy);

/**
 * Begin a single conversion (when in single-shot mode)
 * @param dev Device descriptor
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_start_conversion(i2c_dev_t *dev);

/**
 * Read last conversion result
 * @param dev Device descriptor
 * @param value Last conversion result
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_get_value(i2c_dev_t *dev, int16_t *value);

/**
 * Read last conversion result for ADS101x
 * @param dev Device descriptor
 * @param value Last conversion result
 * @return `ESP_OK` on success
 */
esp_err_t ads101x_get_value(i2c_dev_t *dev, int16_t *value);

/**
 * Read the programmable gain amplifier configuration
 * (ADS1114 and ADS1115 only).
 * Use `ads111x_gain_values[]` for real voltage.
 * @param dev Device descriptor
 * @param gain Gain value
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_get_gain(i2c_dev_t *dev, ads111x_gain_t *gain);

/**
 * Configure the programmable gain amplifier (ADS1114 and ADS1115 only)
 * @param dev Device descriptor
 * @param gain Gain value
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_set_gain(i2c_dev_t *dev, ads111x_gain_t gain);

/**
 * Read the input multiplexer configuration (ADS1115 only)
 * @param dev Device descriptor
 * @param mux Input multiplexer configuration
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_get_input_mux(i2c_dev_t *dev, ads111x_mux_t *mux);

/**
 * Configure the input multiplexer configuration (ADS1115 only)
 * @param dev Device descriptor
 * @param mux Input multiplexer configuration
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_set_input_mux(i2c_dev_t *dev, ads111x_mux_t mux);

/**
 * Read the device operating mode
 * @param dev Device descriptor
 * @param mode Device operating mode
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_get_mode(i2c_dev_t *dev, ads111x_mode_t *mode);

/**
 * Set the device operating mode
 * @param dev Device descriptor
 * @param mode Device operating mode
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_set_mode(i2c_dev_t *dev, ads111x_mode_t mode);

/**
 * Read the data rate
 * @param dev Device descriptor
 * @param rate Data rate
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_get_data_rate(i2c_dev_t *dev, ads111x_data_rate_t *rate);

/**
 * Configure the data rate
 * @param dev Device descriptor
 * @param rate Data rate
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_set_data_rate(i2c_dev_t *dev, ads111x_data_rate_t rate);

/**
 * Get comparator mode (ADS1114 and ADS1115 only)
 * @param dev Device descriptor
 * @param mode Comparator mode
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_get_comp_mode(i2c_dev_t *dev, ads111x_comp_mode_t *mode);

/**
 * Set comparator mode (ADS1114 and ADS1115 only)
 * @param dev Device descriptor
 * @param mode Comparator mode
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_set_comp_mode(i2c_dev_t *dev, ads111x_comp_mode_t mode);

/**
 * Get polarity of the comparator output pin ALERT/RDY
 * (ADS1114 and ADS1115 only)
 * @param dev Device descriptor
 * @param polarity Comparator output pin polarity
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_get_comp_polarity(i2c_dev_t *dev, ads111x_comp_polarity_t *polarity);

/**
 * Set polarity of the comparator output pin ALERT/RDY
 * (ADS1114 and ADS1115 only)
 * @param dev Device descriptor
 * @param polarity Comparator output pin polarity
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_set_comp_polarity(i2c_dev_t *dev, ads111x_comp_polarity_t polarity);

/**
 * Get comparator output latch mode, see datasheet.
 * (ADS1114 and ADS1115 only)
 * @param dev Device descriptor
 * @param latch Comparator output latch mode
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_get_comp_latch(i2c_dev_t *dev, ads111x_comp_latch_t *latch);

/**
 * Set comparator output latch mode (ADS1114 and ADS1115 only)
 * @param dev Device descriptor
 * @param latch Comparator output latch mode
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_set_comp_latch(i2c_dev_t *dev, ads111x_comp_latch_t latch);

/**
 * Set number of the comparator conversions before pin ALERT/RDY
 * assertion, or disable comparator (ADS1114 and ADS1115 only)
 * @param dev Device descriptor
 * @param queue Number of the comparator conversions
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_get_comp_queue(i2c_dev_t *dev, ads111x_comp_queue_t *queue);

/**
 * Get number of the comparator conversions before pin ALERT/RDY
 * assertion (ADS1114 and ADS1115 only)
 * @param dev Device descriptor
 * @param queue Number of the comparator conversions
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_set_comp_queue(i2c_dev_t *dev, ads111x_comp_queue_t queue);

/**
 * Get the lower threshold value used by comparator
 * @param dev Device descriptor
 * @param th Lower threshold value
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_get_comp_low_thresh(i2c_dev_t *dev, int16_t *th);

/**
 * Set the lower threshold value used by comparator
 * @param dev Device descriptor
 * @param th Lower threshold value
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_set_comp_low_thresh(i2c_dev_t *dev, int16_t th);

/**
 * Get the upper threshold value used by comparator
 * @param dev Device descriptor
 * @param th Upper threshold value
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_get_comp_high_thresh(i2c_dev_t *dev, int16_t *th);

/**
 * Set the upper threshold value used by comparator
 * @param dev Device descriptor
 * @param th Upper threshold value
 * @return `ESP_OK` on success
 */
esp_err_t ads111x_set_comp_high_thresh(i2c_dev_t *dev, int16_t th);



#ifdef __cplusplus
}
#endif

#endif // end of i2c_ads.h