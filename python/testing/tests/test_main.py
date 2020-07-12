import pytest
import logging
import main
import requests

logger = logging.getLogger()


class MockResponse(object):
    @property
    def status_code(self):
        return 404


def test_foo_status_code(monkeypatch):
    def getmock(*args, **kwargs):
        return MockResponse()

    monkeypatch.setattr(requests, 'get', getmock)

    with pytest.raises(RuntimeError):
        res = main.foo('https://www.google.com')


