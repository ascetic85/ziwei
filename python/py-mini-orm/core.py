# -*- coding: utf-8 -*-
"""
    This is a very simple Object relational mapper (ORM)
    Use this code for fun. It isn't tested on a lot of cases.

    Author: Juan Manuel García <jmg.utn@gmail.com>
"""

class DataBase(object):
    """
        A database agnostic from the engine that you're using.
        At this time implements MySQLdb, sqlite3, psycopg2 but it's easy
        to extend...
    """

    def __init__(self, provider, host='', user='', passwd='', db=''):
        """
            provider: The module for the database connection
                Ej: (MySQLdb, sqlite3, psycopg2)
                是import sqlite3 过后的对象

            host: The Host on the database service is running

            user: user to connect to the database

            passwd: the password of the user

            db: the name of the database
        """

        self.provider = provider # Link to 模块

        # 不同的数据库有不同的连接方式
        self.connections = {"MySQLdb" : self.get_mysql_connection,
                            "sqlite3" : self.get_sqlite_connection,
                            "psycopg2" : self.get_postgre_connection,}

        # 根据provider.__name__ (MySQLdb/sqlite3/psycopg2)获取连接方式
        # self.db: 连接成功后的数据库对象
        # self.cursor: 游标?
        self.connections[self.provider.__name__](host, user, passwd, db)
        self.cursor = self.db.cursor()

        # 不同数据库查询columns 方式不一样
        self.providers = {"MySQLdb" : self.get_mysql_columns,
                          "sqlite3" : self.get_sqlite_columns,
                          "psycopg2" : self.get_postgre_columns,}

    def get_mysql_connection(self, host='', user='', passwd='', db=''):
        """
            Get the connection for mysql databases
        """
        self.db = self.provider.connect(host=host, user=user, passwd=passwd, db=db)

    def get_postgre_connection(self, host='', user='', passwd='', db=''):
        """
            Get the connection for postgres databases
        """
        self.db = self.provider.connect(host=host, user=user, password=passwd, database=db)

    def get_sqlite_connection(self, host='', user='', passwd='', db=''):
        """
            Get the connection for sqlite databases
        """
        self.db = self.provider.connect(db)

    def get_mysql_columns(self, name):
        """
            Get the columns name information for mysql databases
        """
        self.sql_rows = 'Select * From %s' % name
        sql_columns = "describe %s" % name
        self.cursor.execute(sql_columns)
        return [row[0] for row in self.cursor.fetchall()]

    def get_sqlite_columns(self, name):
        """
            Get the columns name information for sqlite databases
        """
        self.sql_rows = 'Select * From %s' % name
        sql_columns = "PRAGMA table_info(%s)" % name
        self.cursor.execute(sql_columns)
        return [row[1] for row in self.cursor.fetchall()]

    def get_postgre_columns(self, name):
        """
            Get the columns name information for postgres databases
        """
        self.sql_rows = 'Select * From "%s"' % name
        sql_columns = """select column_name
                        from information_schema.columns
                        where table_name = '%s';""" % name
        self.cursor.execute(sql_columns)
        return [row[0] for row in self.cursor.fetchall()]

    # 把某张表的字段映射出来
    def Table(self, name):
        """
            A queryable table of the database

            name: the name of the table to query

            return: a Query object
        """
        # 某表的columns
        columns = self.providers[self.provider.__name__](name)
        return Query(self.cursor, self.sql_rows, columns, name)


class Query(object):
    """
        A query Class wihch recursive generate the query-string
    """

    def __init__(self, cursor, sql_rows, columns, name):
        self.cursor = cursor     # 数据库游标
        self.sql_rows = sql_rows # 查询语句
        self.columns = columns
        self.name = name         # 表名

    def filter(self, criteria):
        """
            Implement the "Where" statment of the standard sql
        """
        key_word = "AND" if "WHERE" in self.sql_rows else "WHERE"
        sql = self.sql_rows + " %s %s" % (key_word, criteria)
        return Query(self.cursor, sql, self.columns, self.name)

    def order_by(self, criteria):
        """
            Implement the "Order by" statment of the standard sql
        """
        return Query(self.cursor, self.sql_rows + " ORDER BY %s" % criteria, self.columns, self.name)

    def group_by(self, criteria):
        """
            Implement the "Group by" statment of the standard sql
        """
        return Query(self.cursor, self.sql_rows + " GROUP BY %s" % criteria, self.columns, self.name)

    def get_rows(self):
        """
            Execute the generated query on the database and return a list of Row Objects
        """
        print self.sql_rows
        self.cursor.execute(self.sql_rows)
        return [Row(zip(self.columns, fields), self.name) for fields in self.cursor.fetchall()] # ???

    # !! rows 就调用get_rows !!  ??
    rows = property(get_rows)


class Row(object):
    """
        A row Class dynamically implemented for each table
    """

    def __init__(self, fields, table_name):
        """
            fields: A list of [column_name : value of column]

            table_name: the name of the table
        """
        #Assign the name of the current table to the class
        self.__class__.__name__ = table_name + "_Row"

        for name, value in fields:
            setattr(self, name, value) #self.name = value 把所有的字段都设置为了属性

# setattr示例, !!!强大吧!!! 可以把数据的关系如此的相关联起来都行 ..one2many/many2one/int/....
#class Template(object):
#    def __init__(self):
#        print '__init__ Template'
#
# ids = []
#for x in range(5):
#   t = Template()
#   setattr(t, 'name', x)
#   ids.append(t)
#   
#
#temp2 = Template()
#setattr(temp2, 'ids', ids)
#
#for x in temp2.ids:
#   print x.name


#
# 还有另外一种方式:
# def __getattr__(self, name) 解释obj.field
# def __getitem__(self, name) 解释obj['key'] / obj[1]
#
