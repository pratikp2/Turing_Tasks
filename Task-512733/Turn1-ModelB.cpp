#include <iostream>
using namespace std;

const int Dimension_1 = 512;
const int Dimension_2 = 512;
const int Dimension_3 = 512;

void process_mri_data(double volume[Dimension_1][Dimension_2][Dimension_3])
{
    double sum = 0.0;

    for (int i = 0; i < Dimension_1; i++) {
        for (int j = 0; j < Dimension_2; j++) {
            for (int k = 0; k < Dimension_3; k++) {
                sum += volume[i][j][k];
            }
        }
    }

    cout << "Sum: " << sum << endl;
}

int main()
{
    double volume[Dimension_1][Dimension_2][Dimension_3];

    // Initialise the volume data (not shown in the code snippet for brevity)

    process_mri_data(volume);

    return 0;
}
