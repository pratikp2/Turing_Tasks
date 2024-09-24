import hashlib
import unittest
from unittest.mock import patch
import coverage

ALGORITHMS = ['sha256', 'sha1', 'md5']

def calculate_checksum(data, algorithm='sha256'):
    if algorithm not in ALGORITHMS:
        raise ValueError("Invalid algorithm name. Choose from: {}".format(", ".join(ALGORITHMS)))

    if not isinstance(data, bytes):
        data = data.encode('utf-8')

    checksum = hashlib.new(algorithm, data).hexdigest()
    return checksum

# Test class for calculate_checksum function with multiple algorithms
class TestChecksum(unittest.TestCase):

    def test_calculate_checksum_with_different_algorithms(self):
        test_data = "Hello, this is a test."
        expected_checksums = {
            'sha256': '9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08',
            'sha1': '2a5d213ca5e54bd3a95d5d44a357142c53fb5a44',
            'md5': 'd41d8cd98f00b204e9800998ecf8427e'
        }
        for algorithm in ALGORITHMS:
            with self.subTest(algorithm=algorithm):
                result = calculate_checksum(test_data, algorithm)
                self.assertEqual(result, expected_checksums[algorithm])

    def test_calculate_checksum_with_invalid_algorithm(self):
        with self.assertRaises(ValueError) as cm:
            calculate_checksum("Test data", algorithm="invalid_algorithm")
        self.assertIn("Invalid algorithm name", str(cm.exception))

    @patch('hashlib.new')
    def test_calculate_checksum_exception(self, mock_new):
        mock_new.side_effect = Exception("Some error")
        data = "Test data"
        with self.assertRaises(Exception) as cm:
            calculate_checksum(data)
        self.assertEqual(str(cm.exception), "Some error")

if __name__ == '__main__':
    # Run the tests
    unittest.main()

    # Code coverage analysis
    cov = coverage.Coverage()
    cov.start()
    unittest.main()
    cov.stop()
    cov.save()
    cov.report()