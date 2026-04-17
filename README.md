# localtimes-cli

`localtimes-cli` is a simple command-line tool written in C that displays the current time across various timezones. It uses the standard C library's timezone handling and allows for highlighting specific "important" timezones and your "current" timezone via configuration.

## Features

- Displays current time for multiple timezones.
- Configurable list of timezones.
- Highlighting support:
  - **Green**: Your current timezone.
  - **Yellow**: Important timezones (standard 16-color ANSI so basic terminals render it correctly).
- Simple, dependency-free (standard C and POSIX).

## Prerequisites

- A C compiler (e.g., GCC).
- `make` utility.
- A POSIX-compliant environment (for `setenv`, `gettimeofday`, etc.).

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/c1t0d0s0/localtimes-cli.git
   cd localtimes-cli
   ```

2. Build and install the project:
   ```bash
   make
   make install
   ```
   *Note: This will install the `localtimes` binary to `~/bin`.*

## Configuration

The tool is configured via `config.yml`. The `Makefile` parses this file to generate a header file (`zones.inc`) at build time.

- `timezones`: A list of IANA timezone names to display.
- `color.current`: The timezone to highlight in green.
- `color.important`: A list of timezones to highlight in yellow.

Example `config.yml`:
```yaml
timezones:
  - "UTC"
  - "Asia/Tokyo"
  - "America/Los_Angeles"
color:
  current: "Asia/Tokyo"
  important:
    - "America/Los_Angeles"
```

*Note: After modifying `config.yml`, you must run `make` again to apply the changes.*

## Usage

Run the installed binary:
```bash
localtimes
```

## License

This project is licensed under the [LICENSE](LICENSE) file.
