# Particle-dst
DST switching made simple!

## What is it?
Particle-dst is a simple Particle library that can be used to switch manually or automatically DST all over the world on Partcle devices!

## Installation
Particle-dst is easy to install because it is a normal Particle library.
There are three ways to install this library:

### Command Line Interface ([CLI](https://www.particle.io/products/development-tools/particle-command-line-interface))
First of all, go to your project directory:
```bash
cd /path/to/your/fantastic/project
```
Then install the library with the following command:
```bash
particle library add particle-dst
```

### Web IDE ([Build](https://build.particle.io))
1. Select your project or create a new one
2. Click on `Libraries` in the left sidebar
3. In the search field type `dst`
4. Select `particle-dst`
5. Click on `ÌNCLUDE IN PROJECT`

### Desktop IDE ([Dev](https://www.particle.io/products/development-tools/particle-desktop-ide))
1. Select your project or create a new one
2. Click on `Browse and manage Particle libraries` in the left sidebar
3. In the search field type `dst`
4. In the `particle-dst` panel click on `Use`

## How to use it
### 1) Limits definition
The library enable and disable DST using two limits that define the beginning and the end dates of DST in your country.
Limits can be created using the specific type provided by the library:
```C++
// create the two limits
dst_limit_t beginning;
dst_limit_t end;

// define beginning of DST
beginning.hour = 2;
beginning.day = DST::days::tue;
beginning.month = DST::months::feb;
beginning.occurrence = 2;

// define end of DST
end.hour = 3;
end.day = DST::days::wed;
end.month = DST::months::oct;
end.occurrence = 2;
```

To define days and months you can use the **[Particle numbering](https://docs.particle.io/reference/firmware/photon/#weekday-)** or you can easily use the **enumerators** provided by the library. *(The values will be converted to the Particle numbering)*
```C++
beginning.day = DST::days::tue;
// same as
beginning.day = 3; // tuesday
```
```C++
beginning.month = DST::months::feb;
// same as
beginning.months = 2; // february
```

The **occurrence** indicates in which week of the target month the DST change.
It could have positive and negative values to indicate if the occurrence is from the beginning or the end of the month:
- **positive**: occurrence from the beginning of the month
- **negative**: occurrence from the end of the month
```C++
beginning.occurrence = 1; // first week
beginning.occurrence = -1; // last week
```

### 2) Initialization
To start using the library, initialize it with the two limits. The last parameter indicates the DST offset in your country.
```C++
DST dst;
dst_limit_t beginning;
dst_limit_t end;

void setup() {
  // initialize limits
  // ...

  dst.begin(beginning, end, 1); // DST adds 1 hour
}
```

### 3) Usage
There are two methods to use this library: **manual** mode where the user application has to periodically check if the DST has changed or **automatic** mode where the library switch DST on its own.

### Manual mode
In manual mode the user has to periodically trigger the library to check if DST changed.
To switch DST, simply call one method defined in the library:
```C++
bool enabled = dst.check();
// returns true if DST is enabled and false if it is disabled
Serial.printlnf("DST: %s", enabled ? "enabled" : "disabled");
```

### Automatic mode
In automatic mode the library checks every hour if DST is enabled or disabled automatically without the need of any user interaction.
Simply activate the automatic mode passing `true` to the `automatic()` method and you're done!

_**NOTE:** You have to enable the automatic mode after the initialization of the library otherwise it will don't work!_
```C++
dst.begin(beginning, end, 1);
// ...

dst.automatic(true); // enable automatic mode
```
You can disable the automatic mode whenever you want passing `false` to the `automatic()` method:
```C++
dst.automatic(false); // disable automatic mode
```

## Other features
With particle-dst you can get the timestamp of the beginning and the end of DST in the current year:
```C++
int beginning = dst.beginning();
// example: 1487037600

int end = dst.end();
// example: 1507690800
```

Moreover it is possible to get a formatted string of the limits of the DST in the current year:
```C++
char beginning[] = dst.beginning("%a, %d %B @ %R");
// example: Tue, 14 February @ 02:00

char end[] = dst.end("%a, %d %B @ %R");
// example: Wed, 11 October @ 03:00
```

The library supports all the [Particle format strings](https://docs.particle.io/reference/firmware/photon/#format-):
- `TIME_FORMAT_DEFAULT`
- `TIME_FORMAT_ISO8601_FULL`
- string based on `strftime()` (docs: http://www.cplusplus.com/reference/ctime/strftime/)

## Help me
I've tried to develop this library to be easy to use without having to write many lines of code for doing a simple activity.
If you have some suggestions or you found a bug (*oh no!*), please send me an e-mail at luca.morandini98@gmail.com!

That's all folks!

#### Thanks and happy coding!
