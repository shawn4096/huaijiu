// taohong.c

inherit NPC;

void create()
{
	set_name("������", ({ "zhongnian qifu","qifu","zhongnian" }) ); 
	set("gender", "Ů��" );
	set("age", 33);
	set("long", "һ�������򸾣���ͷ��������ͷɢ�����·��ۻ����á�\n"); 
	set("combat_exp", 1000);
 
	setup();

	set("chat_chance", 3);
	set("chat_msg", ({
		"�������૵ص�����ү���ϼ���Ҫ��ǽ����ô�ֵ��ң���....�ֲ�����Ϲ˵��\n",
		"�����򸾾�����֣����������ʲô�ط������ϵã����ҵ�����ȥ��\n",
		"�����򸾵�����ү�ֲ��ǲ��ţ�����...����....����û˵����үȴ�����ҳ�����\n",	 
	}));

        carry_object(ARMOR_D("cloth"))->wear();
}
