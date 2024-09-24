import hashlib
import unittest
from unittest.mock import patch
import coverage

SUPPORTED_HASH_ALGORITHMS = ['sha256', 'md5', 'sha1', 'sha512']

def calculate_checksum(data, algorithm='sha256'):

	if algorithm not in SUPPORTED_HASH_ALGORITHMS:
		raise ValueError(f"Invalid algorithm: {algorithm}. Supported algorithms: {SUPPORTED_HASH_ALGORITHMS}")

	if not isinstance(data, bytes):
		data = data.encode('utf-8')

	checksum_func = getattr(hashlib, algorithm)
	checksum = checksum_func(data).hexdigest()
	return checksum


class TestChecksum(unittest.TestCase):

	def test_calculate_checksum_with_supported_algorithms(self):
		data = "Hello, this is a test."
		for algorithm in SUPPORTED_HASH_ALGORITHMS:
			with self.subTest(algorithm=algorithm):
				expected_checksum = hashlib.new(algorithm, data.encode('utf-8')).hexdigest()
				result = calculate_checksum(data, algorithm)
				self.assertEqual(result, expected_checksum)

	def test_calculate_checksum_with_unsupported_algorithm(self):
		data = "Test data"
		with self.assertRaises(ValueError) as cm:
			calculate_checksum(data, algorithm='unsupported')
		self.assertEqual(str(cm.exception), "Invalid algorithm: unsupported. Supported algorithms: ['sha256', 'md5', 'sha1', 'sha512']")

	def test_calculate_checksum_with_bytes_data(self):
		data = b"Hello, this is a test in bytes."
		for algorithm in SUPPORTED_HASH_ALGORITHMS:
			with self.subTest(algorithm=algorithm):
				expected_checksum = hashlib.new(algorithm, data).hexdigest()
				result = calculate_checksum(data, algorithm)
				self.assertEqual(result, expected_checksum)

if __name__ == '__main__':
	unittest.main()
	cov = coverage.Coverage()
	cov.start()
	unittest.main()
	cov.stop()
	cov.save()
	cov.report()