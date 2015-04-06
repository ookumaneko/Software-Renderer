#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

namespace demoscene
{
	template <class KEY, class VALUE>
	class HashTable
	{
		//Hash Table Structures
		private:

			struct Hash
			{
				KEY key;
				VALUE value;

				Hash& operator =(const Hash& rhs)
				{
					key = rhs.key;
					value = rhs.value;
				}
			};

			struct Node
			{
				Hash hash;
				Node* next;

				Node() : hash(), next(0) {}

				Node& operator =(const Node& rhs)
				{
					hash = rhs.hash;
					next = rhs.next;
				}
			};

		public:

			//--constructor--//
			HashTable<KEY, VALUE>(void);
			~HashTable<KEY, VALUE>(void);

			//--Public Member Methods--//
			void  Add			(KEY key, VALUE value);
			bool  TryGetValue	(KEY key, VALUE& out);
			bool  Remove		(KEY key);
			bool  Remove		(VALUE toRemove);
			void  Clear			(bool doDelete = false);

			//--Accessors--//
			int   GetSize		(void) const { return m_size; }

		private:
			
			//--private Methods--//
			void ClearList	(Node *list, bool doDelete);

			//--Members--//
			Node* m_list;
			int   m_size;
	};

	#include "HashTable.inl"

} // end of namespace

#endif // end of _HASH_TABLE_H_