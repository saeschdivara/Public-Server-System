#ifndef PAGINATOR_H
#define PAGINATOR_H

#include "public_server_system_globals.h"

#include "system/web/model/AbstractModel.h"

#include <QtCore/QList>

namespace PublicServerSystem
{
namespace Web
{
namespace View
{

template<typename T>
class PUBLICSERVERSYSTEMSHARED_EXPORT Paginator
{
    public:
        inline Paginator(QList<T *> & list, int pageSize, int currentPage) :
            m_list(list),
            m_pageSize(pageSize),
            m_currentPage(currentPage)
        {}

        int firstPageNumber() const {
            return 1;
        }

        QList<int> pages() const {
            QList<int> p;

            for ( int i = 1; i < m_list.size(); i++) {
                p.append(i);
            }

            return p;
        }

        int nextPage() {
            if ( m_currentPage < m_list.size() ) {
                return m_currentPage+1;
            }

            return -1;
        }

        int lastPageNumber() const {
            return m_list.size();
        }

    protected:
        QList<T *> m_list;
        int m_pageSize;
        int m_currentPage;
};

}
}
}

#endif // PAGINATOR_H
