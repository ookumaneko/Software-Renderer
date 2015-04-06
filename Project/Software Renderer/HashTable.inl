
template <class KEY, class VALUE> 
HashTable<KEY, VALUE>::HashTable() : m_size(0), m_list(0)
{
}

template <class KEY, class VALUE> 
HashTable<KEY, VALUE>::~HashTable()
{
	if ( m_size > 0 )
	{
		Clear( false );
	}
}

template <class KEY, class VALUE> 
void HashTable<KEY, VALUE>::Add(KEY key, VALUE value)
{
	Node *toAdd = new Node;	
	Node *current = this->m_list;

	//assign key and value to the new node
	toAdd->hash.key = key;
	toAdd->hash.value = value;
	toAdd->next = 0;

	if ( m_list != 0 )
	{
		//search for the end of list
		while ( current->next != 0 )
		{
			current = current->next;
		}

		//connect new node (temp) to the list
		current->next = toAdd;
	}
	else
	{
		m_list = toAdd;
		//m_list->hash.value = new VALUE;
	}

	m_size++;
}

template <class KEY, class VALUE> 
bool HashTable<KEY, VALUE>::TryGetValue(KEY key, VALUE& out)
{
	Node *temp = this->m_list;
	bool found = false;

	if ( m_list == 0 )
	{
		return false;
	}

	try
	{
		//search through the list
		while ( temp != 0 )
		{
			//if the key matches
			if ( temp->hash.key == key )
			{
				//send the value to the output parameter
				out = temp->hash.value;
				found = true;
				break;
			}

			temp = temp->next;
		}

		if ( !found )
		{
			throw false;
		}
	}
	catch ( bool e )
	{
		return e;
	}

	return found;
}

template <class KEY, class VALUE> 
bool HashTable<KEY, VALUE>::Remove(KEY key)
{
	Node *temp = this->m_list;
	Node *toDelete = 0;

	if ( m_list->hash.key == key )
	{
		toDelete = m_list;
		m_list = m_list->next;
	}
	else
	{
		//search for a matching key
		while ( temp->next != 0 )
		{
			//if the key was found
			if ( temp->next->hash.key == key )
			{
				//remember which node to delete
				toDelete = temp->next;

				//reconnect the list
				if ( temp->next->next != 0 )
				{
					temp->next = temp->next->next;
				}
				else
				{
					temp->next = 0;
				}

				//delete the select node with the key
				break;
			}

			temp = temp->next;
		}
	}

	if ( toDelete != 0 )
	{
		delete toDelete;
		m_size--;
		return true;
	}

	return false;
}

template <class KEY, class VALUE> 
bool HashTable<KEY, VALUE>::Remove(VALUE toRemove)
{
	Node *temp = this->m_list;
	Node *toDelete = 0;

	if ( m_list->hash.value == toRemove )
	{
		toDelete = m_list;
		m_list = m_list->next;
	}
	else
	{
		//search for a matching key
		while ( temp->next != 0 )
		{
			//if the key was found
			if ( temp->next->hash.value == toRemove )
			{
				//remember which node to delete
				toDelete = temp->next;

				//reconnect the list
				if ( temp->next->next != 0 )
				{
					temp->next = temp->next->next;
				}
				else
				{
					temp->next = 0;
				}

				//delete the select node with the key
				break;
			}

			temp = temp->next;
		}
	}

	if ( toDelete != 0 )
	{
		delete toDelete;
		m_size--;
		return true;
	}

	return false;
}

template <class KEY, class VALUE> 
void HashTable<KEY, VALUE>::Clear(bool doDelete)
{
	if ( m_size > 0 && m_list != 0 )
	{
		ClearList( m_list, doDelete );
	}

	m_size = 0;
	m_list = 0;
}

template <class KEY, class VALUE> 
void HashTable<KEY, VALUE>::ClearList(Node *list, bool doDelete)
{
	if ( list != 0 )
	{
		ClearList( list->next, doDelete );
		if ( doDelete ) 
		{
			//delete list->hash.value;
			//list->hash.value = 0;
		}

		delete list;
		list = 0;
	}
}