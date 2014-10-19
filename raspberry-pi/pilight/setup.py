try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup

config = {
    'description': 'Pi Light',
    'author': 'Frank Blaauw',
    'url': 'frbl.eu.',
    'download_url': 'frbl.eu/pilight_v-0_1.tar.gz',
    'author_email': 'info@frbl.eu',
    'version': '0.1',
    'install_requires': ['nose'],
    'packages': ['pilight'],
    'scripts': [],
    'name': 'pilight'
}

setup(**config)
