// room: /d/xingxiu/store.c

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����������������, ����ά����������Ϊ�����������ϣ�
�����챦��������֮�������Ʒ���Ȳ���ö�١�������������������
���ϵĵ�̺�ϣ��Ա߶������Ļ���ǽ���и����ӣ��Ǹ���Ŀ��(sign)��
LONG);
        set("exits", ([ 
             "east" : __DIR__"yili2",
        ]));

        set("objects", ([
                __DIR__"npc/maimaiti": 1,
                __DIR__"npc/shangren": 1  
        ]));

        set("item_desc", ([ 
"sign" : "������д����
��ԭǮ��ͨ�á�
        ���̾ƺ�(hu)       һ����
        ����(fire)         һ����
        ������(dongbula)   һ����
        ˮ��(shuinang)     ������
        �����(jiunang)    ������ʮ��
        ����Ƥ(yangpi)     ������
        ���(mabian)       ������
        ��Ƥ��(yangpi ao)  �����        
        �����˰�ȹ(ao qun) һǧ��        
        �������䵶(wandao) һǧ�����
        ��(ma dao)       һǧ�����
        ë̺(maotan)       ��ǧ��
        Ԣ���(yuyi cao)   ��ǧ��
        ���(liu huang)    һ����
        ̳��(tan zi)       �����
        
        \n"
]));
    
        set("coor/x",-310);
  set("coor/y",160);
   set("coor/z",0);
   set("coor/x",-310);
 set("coor/y",160);
   set("coor/z",0);
   setup();
}

