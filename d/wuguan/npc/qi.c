//qi.c �ݷ� by river

#include <ansi.h>
inherit NPC;
 
void create()
{
        set_name("�ݷ�", ({ "qi fang","qi","fang", "woman" }));        
        set("gender", "Ů��");
        set("age", 21); 
        set("long", "ԲԲ��������һ˫���ۺ�����ġ�\n");
        set("combat_exp", 3000);
        set("shen_type", 1);
        set("attitude", "friendly");        

        set_skill("force", 30);
        set_skill("strike", 30);
        set_skill("sword", 30);
	set_skill("shenzhao-jing",30);
        map_skill("force", "shenzhao-jing");         
 
        set("inquiry", 
                ([
                        "���" : "�����ҵķ������",
		]));

        setup();
        carry_object(ARMOR_D("cloth"))->wear();
        add_money("silver", 3);
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{      
       if( !ob || environment(ob) != environment() ) return;
       if ( ob ->query("combat_exp") < 300) {
       command("wanfu "+ob->query("id"));
       command("say  ��λ" + RANK_D->query_respect(ob) +"����ݶ���������������֮��ɺͱ������� "HIY HBCYN"chat"CYN"
�������������顣������ɢ��Щҥ�� "HIY HBCYN" rumor"CYN" ,ͬһ���ɵĻ������� "HIY HBCYN" party"CYN"��
���ĺ�ɢ��ҥ��ʱ����Щ�Ѿ��еĶ�������������� "HIY HBCYN"chat* hi"CYN" ���� "HIY HBCYN"semote"CYN"
���Բ����Щ�������˵Ķ��������㻰̫��������ͻᱻ��ͶƱ�رս�̸Ƶ
���� "HIY HBCYN"vote chblk xxx"CYN" Ƶ�������˺�ֻ�еȱ���ͶƱ�򿪡� "HIY HBCYN"vote unchblk
xxx"CYN" ��������������������������������������Ը��� "HIY HBCYN"tell"CYN" ��(��)����
�˸�����ʲô�£�������� "HIY HBCYN"reply"CYN" ���ش������������㻹���Ը�ĳһλ����
��ͬһ������˽����Ļ� "HIY HBCYN"whisper"CYN" �������ϲ����˳������书֮�У�ϲ����
��ɱɱ�ģ�Ȼ���Ҿ��û������Ľ��Ѹ���Ȥ�������Ϊ֮�ɡ�"NOR);
	   }
}                               

 


