//      File    :  /adm/daemons/explored.c
//
inherit F_DBASE;

#define SRCH_DIR "/d/"
#include <ansi.h>
#include <explore.h>
#include <dbase.h>
int explore_level = EXPLORE_LEVEL;
int Check_Illgeal_Target(object target);
int Start_Job(object me, object ob);

void create()
{
        set("channel_id", "��������");
        CHANNEL_D->do_channel( this_object(), "sys", "̽��ϵͳ�Ѿ�������\n");
//      Start_Job();
}

// ����ɱ�ּ���ˮƽ
void Copy_Skill(object me, object ob)
{
        return;
}

mapping *corpse_des = ({
([      "shen"      :     "-1",
        "content"   :     ({
        ([
                 "name" : "�ڷ�˫ɷ",
                 "des"   : "\n����ϸ������ʬ�װ��죬��Ȼ����ʬ���ͷ­�Ϻ�Ȼ�����Ѫ����\n",
                 "tar" : "������һ����Ī���Ǻڷ�˫ɷ��Ϊ�����Ͻ���������",
        ]),
        ([
                 "name" : "��Զɽ",
                 "des"   : "\n����ϸ������ʬ�װ��죬ֻ�������ϼ��⽩Ӳ����������ȥ�������ƣ������������⣬��̽����Ϣ������������ʱ�����ؼ������һ�������֣��߹���ϣ��������ѡ�����Ȼ��������ͻ�����֣���ʱ������\n",
                 "tar"  : "������һ����Ī���ǽ����Ƶ�������������һ���������֮������",
        ]),}),
]),
([      "shen"      :     "1",
        "content"   :     ({
        ([
                "name"  : "�԰�ɽ",
                "des"   : "\n����ϸ������ʬ�װ��죬���������������ʱ��,������ǰ���������,���Ʊ����������һ��\n",
                "tar"   : "������һ����Ī���Ǻպ��������䵱������Ϊ����",
        ]),
        ([
                "name"  : "������",
                "des"   : "\n����ϸ������ʬ�װ��죬�������Ϻ���㣬��ɫ�԰׵ú��ˡ����Ǳ�һ�������ڹ���Ϊ\n",
                "tar"   : "������һ����Ī�����������µ���ϼ�񹦵Ļ�Ԫ�޼���������",
        ]),
        }),
]),
});

// ����
int Check_Dir(object obj)
{
        int l,k;
        string name, objfile;
        string *banned_dir = ({ "death", "wizard","register", "zjch", "bj"});

        k = sizeof(banned_dir);

        for(l=0;l<k;l++) {
                if(strsrch((string)obj, (string)banned_dir[l])>=0)
                return 0;
        }

        if( sscanf(obj, "%s.", name)== 1)
                return 0;

return 1;
}

int Check_File(object obj)
{
        string name;
        
        if( sscanf(obj, "%s.c", name)!= 1)
                return 0;       
        return 1;
}

string Chinese_Dir(string dir)
{
        switch(dir) {
        case "/d/shaolin/"  : return "������";break;
        case "/d/wudang/"   : return "�䵱ɽ";break;
        case "/d/city2/"    : return "������";break;
        case "/d/bj/"       : return "������";break;
        case "/d/gaibang/"  : return "ؤ��";break;
        case "/d/murong/"   : return "Ľ��ɽׯ";break;
        case "/d/wanshou/"  : return "���޹�";break;
        case "/d/xingxiu/"  : return "����";break;
        case "/d/yangzhou/" : return "���ݳ�";break;
        case "/d/city/"     : return "���ݳ�";break;
        case "/d/gumu/"     : return "��Ĺ�ľ�";break;
        case "/d/qz/"       : return "����ɽ";break;
        case "/d/jiaxing/"  : return "���˳�";break;
        case "/d/jqg/"      : return "�����";break;
        case "/d/zjch/"     : return "�Ͻ���";break;
        case "/d/bt/"       : return "����ɽׯ";break;
        case "/d/bdao/"     : return "����";break;
        case "/d/chengdu/"  : return "�ɶ���";break;
        case "/d/diaoyu/"   : return "���㵺";break;
        case "/d/emei/"     : return "����ɽ";break;
        case "/d/gaochang/" : return "�߲�";  break;
        case "/d/guiyun/"   : return "����ׯ";break;
        case "/d/hmy/"      : return "��Ĺ��";break;
        case "/d/huanggon/" : return "�ʹ�";  break;
        case "/d/hs/"       : return "��ɽ";  break;
        case "/d/huashan/"  : return "��ɽ";  break;
        case "/d/liaoguo/"  : return "�ɹ�";  break;
        case "/d/mingjiao/" : return "����";  break;    
        case "/d/mj/"       : return "����";  break;
        case "/d/quanzhou/" : return "Ȫ�ݳ�";break;
        case "/d/shenlong/" : return "������";break;
        case "/d/taishan/"  : return "̩ɽ";  break;
        case "/d/thd/"      : return "�һ���";break;
        case "/d/village/"  : return "��ɽ��";break;
        case "/d/xy/"       : return "������";break;    
        case "/d/xiangyang/": return "������";break;
        case "/d/dali/"     : return "�����";break;
        case "/d/wuliang/"  : return "����ɽ";break;        
        default : return "δ֪����";
        }
}

int Check_Npc(object obj)
{
        int i;
        string name;
        string *banned_name= ({ "С����","ľ��","���","���޳�","������","ƽ��",
                           "���ݹ�ͯ","���޳�","��������","����","���ϰ�",
                           "��ֱ̨��Ա","�����ϰ�","����Ů��","����","��������ҽ��"});

        name = obj->query("name");

        if( member_array(name, banned_name)!=-1 ) {
                return 0;
        }

 write(sprintf("%d ",clonep(obj)));
        if( !obj->is_character()
        ||  userp(obj)
        ||  obj->query("race")!="����" )
                return 0;

return 1;
}

string Get_Dir()
{
        int j;
        mixed *ob;

        ob = get_dir(SRCH_DIR);
        ob = filter_array(ob, (: Check_Dir :));

        j=sizeof(ob);
        j=random(j);

        ob[j]=SRCH_DIR+(string)ob[j]+"/";
        printf("Dir: "+ob[j]+"\n");
        return ob[j];
}


string Get_File(string dir_name)
{
        int max_filter, max, i, k;
        string err;
        mixed *ob;
        object obb;
        mapping exits;
        
        ob = get_dir(dir_name);
        ob = filter_array(ob, (: Check_File :));

        for(i=0;i<sizeof(ob);i++) {
//                      err=catch(call_other(dir_name+(string)ob[i]));
                        err=catch(obb=load_object(dir_name+(string)ob[i]));
                        if (err) continue;
                        obb=load_object(dir_name+(string)ob[i]);
                        if(!objectp(dir_name+(string)ob[i])) continue;
                        exits=obb->query("exits");
                        if(!mapp(exits)) continue;
                        
        }

        i=random(sizeof(ob));
        ob[i]=dir_name+(string)ob[i];

        if(!err && !ob[i]->query("race")
        && ob[i]->query("short")) {
                printf("File: "+(string)ob[i]+"\n");
                return (string)ob[i];
        }
        else return Get_File(dir_name);
}
int Check_Illgeal_Target(object target)
{
        // ��ֹ���������NAME��ͬ��
        if(target->query("name") == this_object()->query("last_target"))
                return 0;

        return 1;
}

string Check_Family(string npcfile)
{
        string family;
        family = npcfile->query("title");
        if(!family) family="";
        return family;
}

string Check_Family1(string npcfile)
{
        string family;
        family = npcfile->query("family/family_name");
        if(!family) family="";
        return family;
}

string Get_Npc()
{
        string family, times, npcfile;
        int i, size;
        object target;
        object *living;


        living=filter_array(livings(), (: Check_Npc :));
write(sprintf("%d ",sizeof(livings())));
        size=sizeof(living);
write(sprintf("%d",size));
        i=random(size);

        while(1) {
                target=living[i];
                if( Check_Illgeal_Target(target)) {
                        npcfile=file_name(target);
                        printf("Npc:%s\n", npcfile);
                        return npcfile;
                }
                i++;
                if ( i >= size ) i=0;
                if ( i == size ) break;
        }

}

void get_corpse(string npc_file, string file_name, object me)
{

        int i, k, p;
        object *inv;
        object corpse, room, victim;

        if(!(victim = find_object(npc_file)))
             victim = load_object(npc_file);
        if(!(room = find_object(file_name)))
             room = load_object(file_name);
        corpse = new(EXPLORE_OB);
        corpse->move(file_name);
//      corpse->move("/u/lancy/workroom");
//      corpse->set("dead_message","");
//      corpse->die();        
        corpse->set_name( victim->name(1) + "��ʬ��", ({ "corpse" }) );
        corpse->set("age", victim->query("age"));
        corpse->set("gender", victim->query("gender"));
        corpse->set("victim_name", victim->name(1));
        corpse->set("victim_id", victim->query("id"));
        corpse->set("victim_exp", victim->query("combat_exp"));
        corpse->set("victim_shen", victim->query("shen"));
        corpse->set_weight( victim->query_weight() );   
        corpse->set_max_encumbrance( victim->query_max_encumbrance() );
//      corpse->move(file_name);
        if( !wizardp(victim) ) {
                inv = all_inventory(victim);
                inv -= ({ 0 });
                i = sizeof(inv);
                while(i--) {
                        if( (string)inv[i]->query("equipped")=="worn" ) {
                                inv[i]->move(corpse);
                                if( !inv[i]->wear() ) inv[i]->move(environment(victim));
                        }
                        else inv[i]->move(corpse);
                }
        }
        corpse->set("long", victim->long(1)
                + "Ȼ����" + gender_pronoun(victim->query("gender")) 
                + "�Ѿ����ˣ�ֻʣ��һ��ʬ�徲�����������\n");        
        
        

        if( (int)me->query("shen") < 0) k=0;
        if( (int)me->query("shen") > 0) k=1;
        p=sizeof(corpse_des[k]["content"]);
        p=random(p);
        corpse->set("corpse_des", corpse->query("long")+corpse_des[k]["content"][p]["des"]);
        
        return;
}

int Start_Job(object me, object ob)
{
        mapping my, tmp_my;
        string dir_name, file_name, chinese_name, npcfile, name, family;
        int exp, num;
        object shashou/*, corpse, room*/;
        object *living;

        seteuid(getuid());

        npcfile = Get_Npc();
        dir_name = Get_Dir();
        file_name = Get_File(dir_name);
        chinese_name = Chinese_Dir(dir_name);
        family = Check_Family(npcfile);
        name = file_name->query("short");
        if( explore_level > EXPLORE_LEVEL ) {
                remove_call_out("Start_Job");
                return 1;
        }
        get_corpse(npcfile, file_name, me);
        this_object()->set("last_target", npcfile->query("name"));
        CHANNEL_D->do_channel( this_object(), "chat", sprintf(HIC"��˵ "+HIW + "��"+ HIY +"%s%s" + HIW + "�� " + HIC + "ǰЩ������ " + HIW + "��%s��%s"+ HIW + "��"+ HIC + " ������������λӢ����̽�þ���������ʤ�м���"NOR, family,npcfile->query("name"),chinese_name,name));
//call_out("Start_Job", 150, this_object());
        return 1;

//      if( exp > 20000 ) {  // exp ���� 20k �Ϳ�����Job

//              shashou = new("/clone/npc/shashou"); // ����һ��ɱ��

// ��ʼ����shashou����ˮƽ
//              Copy_Skill(me, ob);
// ����������ͷ������ʦ�ļ���ˮƽ

//              shashou->set("catch_user_id",me->query("id"));
//              shashou->move(environment(me));

//      }

}

int set_explore(int level)
{
        if( geteuid(previous_object()) != ROOT_UID )
                return 0;
        explore_level = level;
        return 1;
}

