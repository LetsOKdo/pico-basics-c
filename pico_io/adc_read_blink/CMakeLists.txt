# Add executable. Default name is the project name, version 0.1

add_executable(adc_read_blink adc_read_blink.c )

pico_set_program_name(adc_read_blink "adc_read_blink")
pico_set_program_version(adc_read_blink "0.1")

pico_enable_stdio_uart(adc_read_blink 1)
pico_enable_stdio_usb(adc_read_blink 0)

# Add the standard library to the build
target_link_libraries(adc_read_blink pico_stdlib hardware_adc)

pico_add_extra_outputs(adc_read_blink)

