// By River 98/12/
inherit ROOM;

void create()
{
        set("short", "������");
	set("long", @LONG
���Ǵ����˾�����أ��ӹܵ���Ҫ��һЩ����֮��ľ��׺���⣬��˸�
���к��壬���壬�����壬�����壬׳���Ա��һ������ʾ���������⣬����
������ͨ�룬�Ա�Ѷ�ʡ���������̬���ͣ���������ǰ���嵭����
LONG
	);
	set("exits",([ 
             "north" : __DIR__"nanjie2",
        ]));

        set("objects", ([
                __DIR__"npc/yayi" : 2,
        ]));
    
	set("coor/x",-320);
  set("coor/y",-470);
   set("coor/z",-20);
   setup();
}
