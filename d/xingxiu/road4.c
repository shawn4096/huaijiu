inherit ROOM;

void create()
{
        set("short", "���ﳤ��");
        set("long", @LONG
���������ﳤ�ǵļ����ˣ���ǽ�ߴ��ʵ�����治ʱ�������׵�ʿ��
�������߶�Ѳ�ߡ������߱��������ı߹ء������ء�������ͨ����ԭ������
���ȶɹ��ƺӡ�
LONG);
        set("exits", ([
          "southeast" : __DIR__"road3",
          "west" : __DIR__"fangpan",
        ]));

        set("outdoors", "jyg");

        set("coor/x",-170);
  set("coor/y",70);
   set("coor/z",0);
   setup();
}
