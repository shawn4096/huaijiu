inherit ROOM;
void create()
{
        set("short","�ĳ�����");
        set("long", @LONG
��һ�߽��ⷿ�䣬ֻ���������ᣬ��������������֮����˵�������ö�
�����������Ѿ����������ˣ�����һ��Ĵ�磬���ھ۾�����������ӣ�̧
ͷһ�����ң�����һ�顣
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
         "east" : __DIR__"duchang",
         "north" : __DIR__"duchang4",
  
]));
        set("item_desc", ([
                "sign": @TEXT


���ӵĶķ���

�����������ࣾ����������

���ࣺ����������������������
������          ��С    ������������    һ��һ
����            �Ĵ�    ��������������  һ��һ
������          ��Χ��  ����������ͬ�㣩һ����ʮ��
��������        �ĵ���                  һ���

���ӣ�
��������������
����ʮ����С��

TEXT
        ]) );
        set("no_fight",1);
        set("no_sleep",1);
        set("objects", ([
        __DIR__"npc/pingwei" : 1,
                        ]) );
        set("coor/x",80);
  set("coor/y",-20);
   set("coor/z",0);
   setup();
}
void init()
{
object me;
me = this_player();
if( me->query("gamble/amount")) {
me->delete("gamble/amount");
me->decrease_skill("betting",1);
}

        add_action("action", ({
                   "dazuo",
                   "du",
                   "exercise",
                   "lian",
                   "practice",
                   "respirate",
                   "study",
                   "tuna"
        }));
}

int action()
{
        write("���޷���������������\n");
        return 1;
}


