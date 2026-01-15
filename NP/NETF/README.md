1.1 Project Description

Design and Implementation of a Small Network using Packet Tracer
As a Network Engineer in a small-medium-sized enterprise.
The company is implementing a wired network that must support growth over the next five years.
1.2 Objectives
The primary goal of this project is to create a small network infrastructure based on the Fixed Length Subnet Mask (FLSM) concept. Involving designing Local Area Networks, Wide Area Networks, configuring routers and switches.
1.3 Key Aspects
The project encompasses the following key aspects:
	Network Design: 
•	Subdividing given /24 ipv4 into equal number of subnets based on requirements.
•	Designing simple Local Area Networks (LANs) 
•	Implementing IP addressing using FLSM principles.
	Configuration: 
•	Basic configuration like Ip addresses, default gateway, subnets on of routers and switches. 
•	Setting up static routes between routers for communication between network devices. 
	IPv4 Addressing: 
•	Assigning IP addresses to hosts and network segments. 
•	Understanding subnetting and subnet masks. 
	Implementation of additional networking Addressing: 
•	Improve Security measures. Such as Passwords for different privileges
•	Create a Server, Web services, website domain name for realism. 
	Practical Experience: 
•	Gaining knowledge with network security practices. 
•	Troubleshooting common network issues.
1.4 Expected Outcomes
Understand the practical application of network design and configuration principles. 
Students will gain some valuable insights into real-world networking scenarios. 
Fixed Length Subnet Masking (FLSM) which allows addresses to be evenly distributed to the exact number of hosts that the company requires for each subnet. This will ensure organized usage of IP in the organization of the whole network structure.
Implement static routing on both routers to have communication between the subnets across the local area and network (LAN) as well as in the wide area network (WAN). This allows different devices in different subnets to successfully exchange data.
Better security, such as SSH and by enforcing password policies, user authentication, as well as login timeouts to prevent repeated attempts to login.

Network address: 105.4.100.0

Useable Number of hosts per subnet = 2h-2	(h is the remaining host bits, there are fewer host address available with each bit borrowed)
Number of required subnets ≤ 2sn		(sn is the number of bits borrowed)

Given: 		105.4.100.0
Subnets needed:	5
Subnet A:		12	(useable IP address required)
Subnet B:		8	(useable IP address required)
Subnet C:		2	(useable IP address required)
Subnet D:		24	(useable IP address required)
Subnet E:		5	(useable IP address required)

Subnet needed ≤ 2sn 
		5 ≤ 2sn 
		5 ≤ 23
		5 ≤ 8

h = 8-3 = 5

Useable Number of hosts per subnet = 2h-2
					= 25-2
					=32-2
					=30
24 ≥ 30 (acceptable)
Old Subnet Mask: /24 or 255.255.255.0
Add 3 to 24 for new prefix length

New Subnet Mask: /27 or 255.255.255.224
Number of Bits Borrowed: 3 bits from host
Number of Subnets: 8 Subnets
Number of useable Host per Subnet: 30 Hosts
Useable size of Subnet

0	0	0	0	0	0	0	0
128	64	32	16	8	4	2	1

Binary Representation: 11111111.11111111.11111111.00000000
Since 00000000 therefore 0
255.255.255.0

Binary Representation: 11111111.11111111.11111111.00100000
Add 32 to 0 = 32
Since 00100000 therefore 32
255.255.255.32

Binary Representation: 11111111.11111111.11111111.01000000
Add 64 to 0 = 64
Since 01000000 therefore 64
255.255.255.64

Binary Representation: 11111111.11111111.11111111.01100000
Add 64 & 32 to 0 = 96
Since 01100000 therefore 96
255.255.255.96

Binary Representation: 11111111.11111111.11111111.10000000
Add 128 to 0 = 128
Since 10000000 therefore 128
255.255.255.128

Binary Representation: 11111111.11111111.11111111.10100000
Add 128 & 32 to 0 = 160
Since 10100000 therefore 160
255.255.255.160

Binary Representation: 11111111.11111111.11111111.11000000
Add 128 & 64 to 0 = 192
Since 11000000 therefore 192
255.255.255.192

Binary Representation: 11111111.11111111.11111111.11100000
Add 128 & 64 & 32 = 224
Since 11100000 therefore 192
255.255.255.224

Therefore from 255.255.255.0 to 255.255.255.32 to 255.255.255.64 to 255.255.255.96 to 255.255.255.128 to 255.255.255.192 to 255.255.255.224

The remaining 11100000
Its zeros is the Useable Host bits
