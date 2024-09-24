import hashlib
import unittest
from unittest.mock import patch
import coverage

def calculate_checksum(data):
    if not isinstance(data, bytes):
        data = data.encode('utf-8')
    checksum = hashlib.sha256(data).hexdigest()
    return checksum

# Test class for calculate_checksum function
class TestChecksum(unittest.TestCase):

    def test_calculate_checksum_with_string(self):
        data = "Hello, this is a test."
        expected_checksum = '9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08'
        result = calculate_checksum(data)
        self.assertEqual(result, expected_checksum)

    def test_calculate_checksum_with_bytes(self):
        data = b"Hello, this is a test in bytes."
        expected_checksum = 'c5e478d59288c841aa530db6845c6c8d562513a42f5e453f3469330375a7a34f'
        result = calculate_checksum(data)
        self.assertEqual(result, expected_checksum)

    @patch('hashlib.sha256')
    def test_calculate_checksum_exception(self, mock_sha256):
        mock_sha256.side_effect = Exception("Some error")
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