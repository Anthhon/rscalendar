use std::env;
use chrono::Datelike;

fn print_usage(args: &Vec<String>){
    println!("Usage: {} -y [YEAR] -m [MONTH]", args[0]);
}

fn get_days_in_month(month_n: u8) -> u8{
    let days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];

    match month_n == 0 {
        true => return days[month_n as usize] as u8,
        false => return days[(month_n as usize) - 1] as u8,
    }
}

fn calendar_print(year: &u16, month: &u8, day: &u8, month_days: &u8){
    let today = chrono::Utc::now().date_naive().day() as u8;

    print!("-----{}/{:0>2}/{}-----", day, month, year,);
    for day in 1 ..=*month_days {
        if day % 7 == 1 {
            println!();
        }
        if day == today {
            print!("\x1B[7m"); // Make text colored
        }
        else {
            print!("{:>2}", day);
            print!("\x1B[0m "); // Reset text color
        }
    }
    println!();
}

fn calendar_build(in_year: &u16, in_month: &u8){
    let current_date = chrono::Utc::now().date_naive();
    let mut calendar_year = *in_year;
    let mut calendar_month = *in_month;
    let calendar_day = current_date.day() as u8;
    let days_in_month = get_days_in_month(calendar_month.clone());

    // Get current date in case they are null
    if calendar_year == 0 {
        calendar_year = current_date.year() as u16;
    }
    if calendar_month == 0 {
        calendar_month = current_date.month() as u8;
    } else if calendar_month > 12 {
        panic!("ERROR:Invalid month value!");
    }

    calendar_print(&calendar_year, &calendar_month, &calendar_day, &days_in_month);
}

fn main(){
    let args: Vec<String> = env::args().collect();

    if args.len() > 5 {
        print_usage(&args);
    }

    let mut year: u16 = 0;
    let mut month: u8 = 0;
    let mut iter = args.iter().peekable();

    while let Some(argument) = iter.next() {
        if argument.eq_ignore_ascii_case("-y") {
            // Get next argument as year
            if let Some(next_arg) = iter.next() {
                match next_arg.parse::<u16>() {
                    Ok(in_year) => year = in_year,
                    Err(_) => panic!("ERROR:Invalid year value!"),
                }
            } else {
                panic!("ERROR:Missing year value!");
            }
        }
        if argument.eq_ignore_ascii_case("-m") {
            // Get next argument as month 
            if let Some(next_arg) = iter.next() {
                match next_arg.parse::<u8>() {
                    Ok(in_month) => month = in_month,
                    Err(_) => panic!("ERROR:Invalid month value!"),
                }
            } else {
                panic!("ERROR:Missing month value!");
            }
        }
    }

    calendar_build(&year, &month);
}
