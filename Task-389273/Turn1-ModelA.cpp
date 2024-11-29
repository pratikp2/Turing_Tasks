#include <systemc.h>
#include <iostream>

// Data Acquisition Module
SC_MODULE(DataAcquisition) {
    sc_out<double> data_out;

public:
    SC_CTOR(DataAcquisition) : data_out("data_out") {
        SC_THREAD(process);
    }

private:
    void process() {
        double data;
        while (true) {
            data = sc_time_stamp().to_double() * 10.0; // Generate some simple data
            data_out.write(data);
            wait(10, SC_NS); // Simulate data collection delay
        }
    }
};

// Preprocessing Module
SC_MODULE(Preprocessor) {
    sc_in<double> data_in;
    sc_out<double> data_out;

public:
    SC_CTOR(Preprocessor) : data_in("data_in"), data_out("data_out") {
        SC_THREAD(process);
    }

private:
    void process() {
        double data;
        while (true) {
            data = data_in.read();
            data_out.write(data * 2.0); // Simple preprocessing: double the data
            wait(); // Wait for new data
        }
    }
};

// Output Module
SC_MODULE(OutputModule) {
    sc_in<double> data_in;

public:
    SC_CTOR(OutputModule) : data_in("data_in") {
        SC_THREAD(process);
    }

private:
    void process() {
        double data;
        while (true) {
            data = data_in.read();
            std::cout << "Output: " << data << std::endl;
            wait(); // Wait for new data
        }
    }
};

// Top-level Module
int sc_main(int argc, char* argv[]) {
    sc_signal<double> data_signal1;
    sc_signal<double> data_signal2;

    DataAcquisition data_acquisition("data_acquisition");
    Preprocessor preprocessor("preprocessor");
    OutputModule output_module("output_module");

    data_acquisition.data_out(data_signal1);
    preprocessor.data_in(data_signal1);
    preprocessor.data_out(data_signal2);
    output_module.data_in(data_signal2);

    sc_start(50, SC_NS);
    return 0;
}
