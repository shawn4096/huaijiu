// mushizl.c Ĺ������

inherit ROOM;

void create()
{
         set("short", "Ĺ��ͨ��");
       set("long", @LONG
������Ĺ�����һ��ͨ����ǽ���Ϻܳ�ʪ��������ܺڣ�ǰ������������
�����Һ�ͨ�����Ǻܳ���������һ˿������Զ���չ��������˵�Ӱ���ϵĳ���
��,ӡ�ڵ��ϡ�
LONG
       );
       set("exits", ([
        "south" : __DIR__"fenduo2",
        "west" : __DIR__"xiao-mushi",
    	]));
	set("coor/x",110);
  set("coor/y",70);
   set("coor/z",-10);
   setup();
     }
