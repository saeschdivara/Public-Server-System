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
        inline Paginator(int pageSize, int currentPage) :
            m_pageSize(pageSize),
            m_currentPage(currentPage)
        {
            if (m_pageSize < 1) m_pageSize = 1;
        }

        QList<T *> getList() {
            int startingPoint = (m_currentPage - 1) * m_pageSize;
            m_list = T::objects->getPart(startingPoint, m_pageSize);
            m_fullCount = T::objects->count();
            return m_list;
        }

        QList<T *> list() {

            if ( m_list.size() > 0 )
                return m_list;
            else
                return getList();
        }

        int pageCount() const {
            int pagesCount = m_fullCount / m_pageSize;
            return pagesCount;
        }

        int firstPageNumber() const {
            return 1;
        }

        QList<int> pages() const {
            QList<int> p;

            for ( int i = 1; i < pageCount(); i++) {
                p.append(i);
            }

            return p;
        }

        int previousPage() const {
            if ( m_currentPage > 1 ) {
                return m_currentPage - 1;
            }

            return -1;
        }

        int nextPage() const {
            if ( m_currentPage < 1 ) return 1;
            else if ( m_currentPage < pageCount() ) return m_currentPage + 1;
            else return -1;
        }

        int lastPageNumber() const {
            return m_list.size();
        }

    protected:
        QList<T *> m_list;
        int m_pageSize;
        int m_currentPage;
        int m_fullCount;
};

}
}
}

#endif // PAGINATOR_H
