// baoxiang.c ����
// by iceland

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string ask_miji();
string ask_jiaohuan();

void create()
{
        set_name("����", ({ "bao xiang", "baoxiang" ,"bao","xiang"}));
        set("long",@LONG
����Ѫ���������������ӣ����÷�ͷ��������汩Ű֮ɫ��
����������ķ��Ź⣬�����ؽ����еĳ����ˡ�
LONG
        );
        set("title", HIR "������Ѫ���������µ���" NOR);
        set("gender", "����");
	set("class", "huanxi");
        set("age", 39);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 28);
        set("int", 15);
        set("con", 25);
        set("dex", 28);
        set("max_qi", 900);
        set("eff_jing", 300);
	set("max_jing",300);
        set("neili", 1100);
        set("max_neili", 1100);
        set("jiali", 30);
        set("combat_exp", 300000);
        set("score", 30000);
	set("unique", 1);
        set("no_get","���������˵̫���ˡ�\n");

        set_skill("huanxi-chan", 80);
        set_skill("literate", 60);
        set_skill("force", 80);
        set_skill("longxiang-boruo", 80);
        set_skill("dodge", 80);
        set_skill("yuxue-dunxing", 80);
        set_skill("hand", 70);
        set_skill("dashou-yin", 70);
        set_skill("claw", 70);
        set_skill("tianwang-zhua", 70);
        set_skill("parry", 80 );

        map_skill("force", "longxiang-boruo");
        map_skill("dodge", "yuxue-dunxing");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "tianwang-zhua");
        map_skill("claw", "tianwang-zhua");

        prepare_skill("hand","dashou-yin");
        prepare_skill("claw","tianwang-zhua");

        set("inquiry", ([
                "Ѫ���ؼ�" : (: ask_miji :),
                "����" : (: ask_jiaohuan :),
                "Ѫ������" : "������ʦ�������������������У�����������\n",
                "����" : "��˵������ʦ��Ѫ������ɣ������пɲ����׼�����\n" ,
                "����" : "����������Ҳ�Ǵ˵����ˣ��л������������ϡ�\n",
                "С�" : "�������ҵ�֪����֪������Ȥ���ڣ���ʲô��Ϣ���ǽ���������\n",
        ]));
        set("miji_count", 1);

        create_family("������", 12, "����");
        set("class", "huanxi");

        setup();
        carry_object("/d/xueshan/npc/obj/gongde-jiasha")->wear();

        add_money("silver",10);
}

void attempt_apprentice(object ob)
{
        if ((string)ob->query("family/family_name") != "������") {
                command("say"+ RANK_D->query_respect(ob) +
                        "���Ǳ��µ��ӣ������ﵷʲô�ң���");
                return;
        }

        if ((int)ob->query_skill("huanxi-chan", 1) < 50) {
                command("say ��ϲ���Ǹ����书֮���������ڼ������ɡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ��������������б��ŵ��ķ��ɡ�");
                return;
        }

        if ((string)ob->query("class") != "huanxi") {
                message_vision("�����˿���ͷ�������������Լ��Ĺ�ͷ��",this_player());
                command("say �㻹û���ң����ܱ�ʾ���������̷ϲ���Ҳ������㡣");
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "�������¾��ģ������̷��ҷ��������Ұɡ�");
                return;
        }
        command("say �ðɣ��Ժ���ͺú��̷��ү�Ұɡ�");
        command("recruit " + ob->query("id"));

        ob->set("title", HIR "������Ѫ���ŵ���������" NOR);
}
 string ask_miji()
{
        this_player()->set_temp("jiaohuan",1); 
        return  "Ѫ���ؼ��Ǳ���һ�����飬�Ǳ�����ǰһλ��ɮ��¼�����ģ�
������Ҫ��һ�׵��������׵�����������...���������ʲô���ؼ�����
������һ�û���꣬�������ġ�\n" ;
}
 string ask_jiaohuan()
{
        if  ((int)this_player()->query_temp("jiaohuan")) {
          this_player()->set_temp("miji",1);
          return "����ʲô���书����Ҫ���أ�������ʲô�������һ���";
         }
        else {
          message_vision("�����Ի�Ŀ��˿�$N��\n",this_player());
         }
}
 int accept_object(object who, object ob)
{
        object obj;
        
        if( !who || environment(who) != environment() ) {return 0;}
        if ( !objectp(ob) ) {return 0; }
        if ( !present(ob, who) ) return notify_fail("��û�����������");

        if ((string)ob->query("id") == "chungong tu" ) {
            if (query("miji_count") > 0) {
               command("ah");
               message_vision("����ϲ��ü����Ц�������㵸��\n",this_player());
               command("say ������Ǹ��������������㵽�ģ�̫������");
               message_vision(
"��������$N���ڣ��Ͻ��Ѵ���ͼ���ڻ��У���Ѫ���ؼ�����$N���С�\n",this_player());
               obj=new(MISC_D("xuedao-miji"));
               obj->move(who);
               add("miji_count", -1);
               command("say �ã�����ô����!\n");
               remove_call_out("destroying");
               call_out("destroying", 1, this_object(), ob);
		return 1;
              }
            else { 
               command("ah");
               message_vision("����ϲ��ü����Ц�������㵸��\n",this_player());
               command("say ������Ǹ��������������㵽�ģ�̫������");
               command("say �ã�����ô����!\n");
               remove_call_out("nothing");
               call_out("nothing",2,who);
               remove_call_out("destroying");
               call_out("destroying", 1, this_object(), ob);
               return 1;
             }
          }
        else {
               command("say ������뻻������������!");
               remove_call_out("destroying");
               call_out("destroying", 1, this_object(), ob);
               return 0;
             }
}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}
void nothing(object me)
{
	if (!me) return;
               message_vision("���������ڻ����������͵����˰��죬ʲôҲû�ͳ�����\n", me);
               command("say ���ˣ�������Ѫ���ؼ��Ѿ����˱����ˡ�");
               command("say ���㵹ù���Ȿ����ͼ����Ƚ���ҿ�����ɡ�"); 
               command("shrug");              
}
void init()
{
	object ob;
	ob = this_player();
	if((ob->query("gender")=="Ů��")&&((string)ob->query("family/family_name") != "������") ){
	if(ob->query("per")>=20){
	message_vision(HIY"����ͻȻ����$N��ǰ����ס��ȥ·��\n"NOR,ob);
	message_vision(HIY"�������´�����$N���ٺ���Ц��������\n"NOR,ob);
	command("say ��λ"+RANK_D->query_respect(ob)+"���ߵ���ô������������ȥѽ��");
	ob->start_busy(2);
	}
	else {
	message_vision(HIY"����ͻȻ����$N��ǰ����ס��ȥ·��\n"NOR,ob);
	message_vision(HIY"�������´�����$N�������ֳ�ʧ������ɫ�����һƲ��\n"NOR,ob);
	command("say ��λ"+RANK_D->query_respect(ob)+"��ô������˳�ª��ʵ�����˴�ʧ������");
	ob->start_busy(2);
	}
    }
}
