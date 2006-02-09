/**
 * section: Informations
 * synopsis: Extract informations about Xen domain 0
 * purpose: Demonstrate the basic use of the library to connect to the
 *          hypervisor and extract domain informations.
 * usage: info1
 * test: info1
 * author: Daniel Veillard
 * copy: see Copyright for the status of this software.
 */

#include <stdio.h>
#include <libvirt.h>

/**
 * getDomainInfo:
 * @id: the id of the domain
 *
 * extract the domain 0 informations
 */
static void
getDomainInfo(int id) {
    virConnectPtr conn = NULL; /* the hypervisor connection */
    virDomainPtr dom = NULL;   /* the domain being checked */
    virDomainInfo info;        /* the informations being fetched */
    int ret;

    /* NULL means connect to local Xen hypervisor */
    conn = virConnectOpenReadOnly(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Failed to connect to hypervisor\n");
	goto error;
    }

    /* Find the domain of the given id */
    dom = virDomainLookupByID(conn, id);
    if (dom == NULL) {
        fprintf(stderr, "Failed to find Domain %d\n", id);
	goto error;
    }

    /* Get the informations */
    ret = virDomainGetInfo(dom, &info);
    if (ret < 0) {
        fprintf(stderr, "Failed to get informations for Domain %d\n", id);
	goto error;
    }

    printf("Domains %d: %d CPUs\n", id, info.nrVirtCpu);

error:
    if (dom != NULL)
        virDomainFree(dom);
    if (conn != NULL)
	virConnectClose(conn);
}

int main(int argc, char **argv) {

    getDomainInfo(0);

    return(0);
}
