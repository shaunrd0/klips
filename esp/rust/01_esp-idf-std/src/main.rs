use esp_idf_hal::delay::FreeRtos;
use esp_idf_hal::ledc::*;
use esp_idf_hal::peripherals::Peripherals;
use esp_idf_hal::prelude::*;

fn main() -> anyhow::Result<()> {
    esp_idf_hal::sys::link_patches();

    println!("Configuring output channel");

    let peripherals = Peripherals::take()?;
    // Channel for on-board LED on ESP32
    let mut channel = LedcDriver::new(
        peripherals.ledc.channel0,
        LedcTimerDriver::new(
            peripherals.ledc.timer0,
            &config::TimerConfig::new().frequency(25_u32.kHz().into()),
        )?,
        peripherals.pins.gpio2,
    )?;

    println!("Starting duty-cycle loop");
    let max_duty = channel.get_max_duty();
    // Cycle the channel duty every 2s to visually show that things are working when flashed.
    for numerator in [0, 1, 2, 3, 4, 5].iter().cycle() {
        println!("Duty {numerator}/5");
        channel.set_duty(max_duty * numerator / 5)?;
        FreeRtos::delay_ms(2000);
    }

    // We want this to run forever, so don't let the application terminate.
    loop {
        FreeRtos::delay_ms(1000);
    }
}
