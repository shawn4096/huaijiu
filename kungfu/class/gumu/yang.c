// yang.c ���
// By River 98.8
// Modified by darken

string ask_gmjiuyin();

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_sword();
int pfm_haichao();
void create()
{
        set_name("���",({"yang guo","yang","guo"}));
        set("title",HIW"��Ĺ����"NOR);
        set("nickname",HIY"������"NOR);
        set("long", "�������������µ���������һ�۵����ڲ�ȥһ����Ӣ�ۺ�����\n");
        set("age", 39);
        set("attitude", "friendly");
        set("no_bark",1);
        set("shen", 10000);
        set("per", 30);
        set("str", 40);
        set("int", 30);
        set("con", 40);
        set("dex", 25);

        set("max_qi", 6500);
        set("max_jing", 5000);
        set("neili", 13500);
        set("eff_jingli", 3500);
        set("max_neili", 13500);
        set("jiali", 100);
        set("combat_exp", 2800000);
        set("unique", 1);

        set_skill("sword",300);
        set_skill("dodge",300);
        set_skill("strike",300);
        set_skill("force", 300);
        set_skill("hand", 300);
        set_skill("cuff", 300);
        set_skill("parry", 300);
        set_skill("stick", 300);
        set_skill("staff", 300);
        set_skill("finger",140);
        set_skill("literate", 250);
        set_skill("baituo-shezhang",180);
        set_skill("xiantian-gong",20);
        set_skill("hamagong",300);
        set_skill("medicine",120);
        set_skill("jingmai-xue",80);
        set_skill("qimen-baguazhen",80);
        set_skill("throwing",110);
        set_skill("dagou-bang",220);
        set_skill("bangjue",170);
        set_skill("yuxiao-jian",190);
        set_skill("tanzhi-shentong",160);
        set_skill("yunu-shenfa", 300);
        set_skill("meinu-quanfa",300);
        set_skill("xuantie-jianfa", 300);
        set_skill("anran-zhang", 300);     
        set_skill("quanzhen-jianfa",300);
        set_skill("tianluo-diwang", 300);
        set_skill("yunu-xinjing",300);
        set_skill("jiuyin-zhengong",160);
        set_skill("dafumo-quan",60);
        set_skill("daode-jing",60);
        set_skill("jiuyin-shenfa",130);
        set_skill("qimen-bagua",150);
        set_skill("taoism",100);

        map_skill("force", "yunu-xinjing");        
        map_skill("sword","xuantie-jianfa");
        map_skill("stick","dagou-bang");
        map_skill("staff","baituo-shezhang");
        map_skill("throwing","tanzhi-shentong");
        map_skill("finger","tanzhi-shentong");
        map_skill("dodge", "yunu-shenfa");
        map_skill("parry", "anran-zhang");        
        map_skill("hand", "tianluo-diwang");
        map_skill("cuff", "meinu-quanfa");
        map_skill("strike", "anran-zhang");        
        prepare_skill("strike","anran-zhang");
        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: exert_function, "xinjing" :),
                (: pfm_haichao :),
                (: perform_action, "strike.xiaohun":),
                (: perform_action, "strike.anran":),
        }));
        create_family("��Ĺ��",3,"������");
        set_temp("apply/damage", 70);
        set_temp("apply/dodge", 60);
        set_temp("apply/attack", 60);
        set_temp("apply/armor", 70);
        set("inquiry", ([
           "��Ĺ" : "���ջ�ɽ����Ӣ�۾��������������ڴ��������꣬�������£�����\n"+
                    "�����ڴ˳���һ�����������ӣ�",
           "С��Ů" : "�������Ұ��ޣ�������������",
           "������" : (: ask_sword :),
           "��������" : (: ask_sword :),
           "��Ĺ����" : (: ask_gmjiuyin :),
        ]));

        setup();
        carry_object(BINGQI_D("sword/gangjian"));
        carry_object("/d/gumu/obj/buxue1")->wear();
        carry_object("/d/gumu/obj/pao1")->wear();
}

void attempt_apprentice(object ob)
{
        mapping fam = ob->query("family");
        if(!fam || fam["family_name"] != "��Ĺ��"){
                command("say "+RANK_D->query_respect(ob)+"�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }
        if(ob->query("gender") != "����") {
                command("bow "+ ob->query("id"));
                command("say �ҿ�ֻ����ͽ����ȥ�������������԰ɡ�");
                return;
        }       
        if((int)ob->query_skill("yunu-xinjing", 1) < 120) {
                command("say �ڹ��ǹ�Ĺ�书֮������"); 
                command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ�������ڹ��϶��µ㹦��");
                return;
        }   
        if((int)ob->query_int() < 32 ) {
                command("say �ҵ��书��Ҫ���ߵ����Բ���ѧ�ᡣ");
                command("say Ҫ�ܴﵽ¯����֮��������ʲô�ĵ����޹ؽ�Ҫ������ȴ�ǰ��Ҳ�����á�");
                command("say "+RANK_D->query_respect(ob)+"�����Ի�����Ǳ�����ڣ�������ذɡ�");
                return;
        }
        if((int)ob->query("shen") < 10000){
                command("say �ҹ�Ĺ�������߽����У�һ���������塣");
                command("say ��λ" + RANK_D->query_respect(ob)+"����������ȥ������������º������ɣ�");
                return;
        }
        command("say �ţ����㻹�Ǹ�ѧ����ϣ��Ҿ�������ɣ�");         
        command("chat ��Ĺ�书���ֽ�����"+ ob->name() +"�ɱ���Ϊʦ�������ˣ�");
        command("chat* pat " + ob->query("id"));
        command("recruit " + ob->query("id"));
        ob->set("title",HIW"��Ĺ��������´���"NOR);
//      ob->set("class","sworder");
}

string ask_sword()
{
        object ob=this_player();
        mapping fam = ob->query("family");
        if ( !fam || fam["family_name"] != "��Ĺ��")
                return RANK_D->query_respect(ob) +"���ҹ�Ĺ���ˣ���֪���˻�������";
        if ( fam["generation"] != 4 )
                return RANK_D->query_respect(ob) +"����������´��ˣ����ǵ��Ժ���˵�ɡ�";
        if ( ob->query("shen") < -100000)
                return RANK_D->query_respect(ob) +"а��̫�أ���ض���ǰ��Ҳ��Ը���Ľ�������������";
        if ( ob->query("ygpass"))
                return "�Ҳ����Ѿ���������������������֮����ô��";
        if ( ob->query("gender")=="����"){
                command("pat "+ ob->query("id"));
                command("say ���������������ϣ����������������ڶ��´���Ĺǰ��������������");
                ob->set("ygpass", 1);
                return "������Ϣ���������У����ص��������ں�ˮ�������ľ��ϣ���ú�ȥ����һ�°ɡ�";
        }
        if ( ob->query("gender") == "Ů��"){
          if ((int)ob->query_str() < 35 )
                return "��λ"+RANK_D->query_respect(ob) +"������������Ҫ���ߵ��������㻹����Ŭ��һ���ɡ�";
          if ((int)ob->query_dex() < 35 )
                return "��λ"+RANK_D->query_respect(ob) +"���ں�ˮ����ϰ����������Ҫ���ߵ������㻹����Ŭ��һ���ɡ�";
          if ((int)ob->query_skill("sword", 1) < 200 )
                return "��λ"+RANK_D->query_respect(ob) +"�Ļ���������������������������Եֵ���ˮ�ĳ����";
          if ((int)ob->query_int() < 35 )
                return "��λ"+RANK_D->query_respect(ob) +"�����Ի������ߣ������������Ҫ���Ŀھ���";
          command("pat "+ ob->query("id"));
          command("say ���������������ϣ����������������ڶ��´���Ĺǰ��������������");
          ob->set("ygpass", 1);
          return "������Ϣ���������У����ص��������ں�ˮ�������ľ��ϣ���ú�ȥ����һ�°ɡ�";
        }
}

int pfm_haichao()
{
        object me,weapon;
        me = this_object();
        weapon = present("gangjian",me);
        if( me->is_busy()) return 0;
        if( objectp(weapon)){
          set("jiali", 1);
          command("wield jian");
          command("perform haichao");
          if(random(10) > 5){
            set("jiali", 50);
            command("unwield jian");
          }
          return 1;
        }
        else {
          new(BINGQI_D("sword/gangjian"))->move(me);
          set("jiali", 1);
          command("wield jian");
          command("perform haichao");
          if(random(10) > 5){
            set("jiali", 50);
            command("unwield jian");
          }
          return 1;
        }
        return 1;
}

int accept_object(object me, object ob)
{

	if( me->query("family/family_name") == "��Ĺ��"
	&& ob->query("id") == "duanqing dan" && me->query_temp("gmjiuyin")) {
		if(random(10)<6) {
			command("say ��ö����ҩ�Բ�ǿ��ʵ�����ɲ����ó�����\n");
			command("sigh " + me->query("id"));
			remove_call_out("destroying");
			call_out("destroying", 1, me, ob);
			return 1;
		}
		command("touch "+me->query("id"));
		command("say �ðɣ���Ȼ�ѽ�ҩ�������ң����Ҿͽ�����֮�ش������㡣\n");
		me->delete_temp("gmjiuyin");
		me->set("gmjiuyin",1); 
		remove_call_out("destroying");
		call_out("destroying", 1, me, ob);
		return 1;
	}

	return 0;
}

string ask_gmjiuyin()
{
	mapping fam;
        int skill;
        skill = this_player()->query_skill("jiuyin-zhengong", 1);

	if ( this_player()->query("gmjiuyin"))
		return RANK_D->query_respect(this_player()) + 
		"����֪������֮����������ʣ�\n";
 
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "��Ĺ��")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��\n";
	if ( skill < 150 )
		return RANK_D->query_respect(this_player()) + 
		"��ľ����湦̫��޷�������֮���\n";
	if ( present("duanqing dan", this_player()) )
		return RANK_D->query_respect(this_player()) + 
		"����ȡ�öϳ����鵤��Ϊ�β����佻�����£�\n";

	this_player()->set_temp("gmjiuyin");
	return "����ȡ�öϳ����鵤�����±�Ϊ�����Ĺ���������⡣\n";

}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}