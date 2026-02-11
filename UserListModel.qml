import QtQuick

ListModel {
	id: userListModel
	ListElement {
		username: "imaad"
		password: "123456789"
		fullname: "John Doe"
		email: "john.doe@example.com"
		phone: "+1 555-0101"
		age: 21
		gender: "Male"
		userrole: "Admin"
	}
	// Dummy data produced from ai
	ListElement {
		username: "jdoe92"
		password: "hashed_password_1"
		fullname: "John Doe"
		email: "john.doe@example.com"
		phone: "+1 555-0101"
		age: 30
		gender: "Male"
		userrole: "Admin"
	}

	ListElement {
		username: "asmith_dev"
		password: "hashed_password_2"
		fullname: "Alice Smith"
		email: "alice.s@company.org"
		phone: "+1 555-0202"
		age: 28
		gender: "Female"
		userrole: "Staff"
	}

	ListElement {
		username: "bobby_g"
		password: "hashed_password_3"
		fullname: "Robert Garcia"
		email: "robert.g@webmail.com"
		phone: "+1 555-0303"
		age: 45
		gender: "Male"
		userrole: "Guest"
	}

	ListElement {
		username: "m_chen"
		password: "hashed_password_4"
		fullname: "Mei Chen"
		email: "m.chen@tech.com"
		phone: "+1 555-0404"
		age: 32
		gender: "Female"
		userrole: "Staff"
	}
}
