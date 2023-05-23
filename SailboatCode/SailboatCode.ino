#define GO_TO_MARK 0
#define ROUND_MARK 1
#define CONTROL_UPDATE_US 10000
#define NAV_UPDATE_US 10000000
#define KALMAN_UPDATE_US 100000
#define MARK_NAV_UPDATE_US 1000000

void rudderControl();
void innerKalmanFilter();
void navigationAlgorithm();

long controlTime = 0;
long navigationTime = 0;
long kalmanTime = 0;

double rudderSetpoint = 0f;
double sailSetpoint = 0f;

double lastRudderInput = 0f;
double lastSailInput = 0f;

double lastHeadingError = 0f;
double lastSailError = 0f;

double markCoords[2] = {};

double markPosition[2] = {100, 50};

void setup() {
    initializeGPS();

    getCoordinates(startCoords);
    double* position = calculatePosition(markCoords, startCoords);
    setMarkPosition(position);
}

void loop() {

    long currentTime = micros();
    if (state == GO_TO_MARK) {
        if (currentTime - controlTime >= CONTROL_UPDATE_US) {
            getFastMeasurement();
            innerKalmanFilter();
            rudderControl();
            sailControl();
            controlTime = currentTime;
        }

        if (currentTime - kalmanTime >= KALMAN_UPDATE_US) {
            getGPS();
            outerKalmanFilter();
            kalmanTime = currentTime;
        }

        if (currentTime - navigationTime >= NAV_UPDATE_US) {
            navigationAlgorithm();
            navigationTime = currentTime;
        }
    }

    else if (state == ROUND_MARK) {
        
    }
    
    // State is standby
    else {
        while (true) {
            digitalWrite(13, HIGH);
            delay(1000);
            digitalWrite(13, LOW);
            delay(1000);
        }
    }
}

void rudderControl() {
    
}
